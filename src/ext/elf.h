typedef struct
	{
		unsigned char magic[4]; // 7F E L F
		unsigned char bitclass;
		unsigned char endian;
		unsigned char elfversion; // Must be 1
		unsigned char abi;
		unsigned char abiversion; // ignore
		unsigned char padding[7];
		uint16_t type;
		uint16_t machine;
		uint32_t version;
		// ... there's more we don't really care about in this context
	}
	elf_header_t;

enum {
	ELF_BITCLASS_NONE,
	ELF_BITCLASS_32,
	ELF_BITCLASS_64,
	ELF_BITCLASS_OOB
};
enum {
	ELF_ENDIAN_NONE,
	ELF_ENDIAN_LITTLE,
	ELF_ENDIAN_BIG,
	ELF_ENDIAN_OOB
};
enum {
	ELF_ABI_NONE,
	ELF_ABI_SYSV,
	ELF_ABI_HPUX,
	ELF_ABI_NETBSD,
	ELF_ABI_LINUX,
	ELF_ABI_SOLARIS,
	ELF_ABI_IRIX,
	ELF_ABI_FREEBSD,
	ELF_ABI_TRU64,
	ELF_ABI_ARM,
	ELF_ABI_STANDALONE,
	ELF_ABI_OOB
};
enum {
	ELF_TYPE_NONE,
	ELF_TYPE_RELOCATABLE,
	ELF_TYPE_EXECUTABLE,
	ELF_TYPE_DYNAMIC,
	ELF_TYPE_CORE,
	ELF_TYPE_OOB,
};
enum {
	ELF_MACH_NONE,
	ELF_MACH_X86 = 0x03,
	ELF_MACH_IA64 = 0x32,
	ELF_MACH_AMDX86 = 0x3E,
	ELF_MACH_ARM = 0x28,
	ELF_MACH_AARM = 0xB7,
	ELF_MACH_RISCV = 0xF3,
	ELF_MACH_Z80 = 0xDC
};

char elf_endians[][8] = {
	"Invalid", "Little", "Big" };

char elf_bitclasses[][8] = {
	"Invalid", "32", "64" };

char elf_types[][16] = {
	"Other", "Relocatable", "Executable", "Dynamic Object", "Core File" };

char elf_abis[][16] = {
	"Generic", "SYS-V", "HPUX", "NetBSD", "Linux", "Solaris", "Irix", "FreeBSD", "Tru64", "ARM", "Standalone" };

char elf_machs[0xFF][16] = {
	[ELF_MACH_NONE] = "None",
	[ELF_MACH_X86] = "x86",
	[ELF_MACH_IA64] = "IA-64 (Itanium)",
	[ELF_MACH_AMDX86] = "x86 (AMD)",
	[ELF_MACH_ARM] = "ARM",
	[ELF_MACH_AARM] = "ARM (AArch64)",
	[ELF_MACH_RISCV] = "RISC-V",
	[ELF_MACH_Z80] = "Zilog Z80",
};

void elf_printer (void *filetype, char *in) {
	static char buffer[128];
	elf_header_t * header = (elf_header_t *) in;
	filetype_t * self = (filetype_t *) filetype;

	if ( header->abi >= ELF_ABI_OOB ) { header->abi = 0; }
	if ( header->bitclass >= ELF_BITCLASS_OOB ) { header->bitclass = 0; }
	if ( header->endian >= ELF_ENDIAN_OOB ) { header->endian = 0; }
	if ( header->abi >= ELF_ABI_OOB ) { header->abi = 0; }
	if ( header->type >= ELF_TYPE_OOB ) { header->type = 0; }
	if ( header->machine >= 0xFF ) { header->type = 0; } // Prevent overflow
	if ( elf_machs[header->machine][0] == 0 ) { header->type = 0; } // Prevent nulls

	char * abi = elf_abis[header->abi];
	char * bitclass = elf_bitclasses[header->bitclass];
	char * endian = elf_endians[header->endian];
	char * type = elf_types[header->type];
	char * mach = elf_machs[header->machine];

	snprintf(buffer, sizeof(buffer),
		"ELF %s-bit %s endian %s, %s %s",
		bitclass, endian, type, mach, abi
	);	self->info = buffer;
}
