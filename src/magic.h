#ifndef MAGIC_H
#define MAGIC_H
#define MIME_APPLICATION_GENERIC "application/octet-stream"

	// Allows overriding the default printer function for certain types
typedef void type_parser(void *type, char *in);
void parser_default(void *type, char *in);
int parse_magic(char *in);
long parse_size(char *in);
long get_size(FILE *f);
int parse_scale(long in);

typedef struct {
	char * name;
	char * magic;
	char * mime;
	char * ext;
	char * info;
	int off;
	int len;
	type_parser *getinfo;
}	filetype_t;

extern filetype_t * type;
#include "ext.h"

// TODO: Replace inline strings with #define MIME_TYPE_SUBTYPE so they are reusable
	// https://www.iana.org/assignments/media-types/media-types.txt
	// https://en.wikipedia.org/wiki/List_of_file_formats
	// https://mime-type.com/mime-types
	// https://mimetype.io/all-types
	// https://github.com/tst2005/lua-mimetypes/blob/master/mimetypes.lua
// "file --mime-type %f" can sometimes also be used but is not preferred
#define magic_table_size ( sizeof(magic_table) / sizeof(magic_table[0]) )
filetype_t magic_table [] = {
	// Easily-identifiable Text Files
	{	.name = "Shebang script",
		.magic = "#!", .len = 2, .mime = "application/x-shellscript" },
	{	.name = "PostScript File",
		.magic = "%!", .len = 2, .ext = "ps", .mime = "application/postscript" },
	{	.name = "SSH/Other Key File",
		.magic = "-----BEGIN", .len = 10, .ext = "key", .mime = "application/x-pem-file" },
	{	.name = "XML Document",
		.magic = "<?xml", .len = 5, .ext = "xml", .mime = "application/xml" },
	// Links
	{	.name = "Linux Desktop Entry", // coreutil "file" incorrectly labels these as plaintext
		.magic = "[Desktop Entry]", .len = 15, .ext = "desktop", .mime = "application/x-desktop" },
	{	.name = "Windows Shell Link",
		.magic = "\x4C\x00\x00\x00\x01\x14\x02\x00\x00\x00\x00\x00\xC0\x00\x00\x00\x00\x00\x00\x46", .len = 20, .ext = "lnk" },
	// Raster Image Formats
	{	.name = "Bitmap Image",
		.magic = "BM", .ext = "bmp", .len = 2 },
	{	.name = "GIF Image, version 87",
		.magic = "GIF87a", .len = 6, .ext = "gif", .mime = "image/gif" },
	{	.name = "GIF Image, version 89",
		.magic = "GIF89a", .len = 6, .ext = "gif", .mime = "image/gif" },
	{	.name = "JPEG Image",
		.magic = "\xFF\xD8\xFF", .len = 3, .ext = "jpeg", .mime = "image/jpeg" },
	{ 	.name = "PNG Image",
		.magic = "\x89\x50\x4E\x47", .len = 4, .ext = "png", .mime = "image/png" },
	{	.name = "Quite-OK Image Format",
		.magic = "qoif", .len = 4, .ext = "qoi", .mime = "image/qoi" },
	{	.name = "Tagged Image File, Little-Endian",
		.magic = "\x49\x49\x2A\x00",
		.len = 4, .ext = "tiff", .mime = "image/tiff" },
	{	.name = "Tagged Image File, Big-Endian",
		.magic = "\x4D\x4D\x00\x2A",
		.len = 4, .ext = "tiff", .mime = "image/tiff" },
	{	.name = "WebP Container Format",
		.magic = "WEBP", .len = 4, .off = 8, .ext = "webp", .mime = "image/webp" },
	// Vector Image Formats
	// Audio and Video Containers
	{	.name = "Audio Interchange Format",
		.magic = "AIFF", .len = 4, .off = 4, .ext = "aiff", .mime = "audio/aiff" },
	{	.name = "Audio Video Interleave",
		.magic = "AVI\x20", .len = 4, .off = 8, .ext = "avi", .mime = "video/x-msvideo" },
	{	.name = "Free Lossless Audio Codec",
		.magic = "fLaC", .len = 4, .ext = "flac", .mime = "audio/flac" },
	{	.name = "Waveform Audio",
		.magic = "WAVE", .len = 4, .off = 8, .ext = "wav", .mime = "audio/wav" },
	{	.name = "MIDI Sound File",
		.magic = "MThd", .len = 4, .ext = "mid", .mime = "audio/midi" },
	{	.name = "MP4 Video",
		.magic = "\x66\x74\x79", .off = 4, .len = 3, .ext = "mp4", .mime = "audio/mp4" },
	{	.name = "OGG Vorbis Format",
		.magic = "OggS", .len = 4, .ext = "ogg", .mime = "audio/ogg" },
	{	.name = "Quite-OK Audio Format",
		.magic = "qoaf", .len = 4, .ext = "qoa", .mime = "audio/qoa" },
	{	.name = "Tagged MP3 Audio",
		.magic = "ID3", .len = 3, .ext = "mp3", .mime = "audio/mp3" },
	// Font Formats
	{	.name = "OpenType Font",
		.magic = "OTTO", .len = 4, .ext = "ttf", .mime = "font/ttf" },
	{	.name = "WOFF Font 1.0",
		.magic = "wOFF", .len = 4, .ext = "woff", .mime = "font/woff" },
	{	.name = "WOFF Font 2.0",
		.magic = "wOF2", .len = 4, .ext = "woff2", .mime = "font/woff2" },
	// Other Multimedia
	{	.name = "Blender File Format",
		.magic = "BLENDER", .len = 7, .ext = "blend", .mime = "application/x-blender" },
	{	.name = "FL Studio Project",
		.magic = "FLhd", .len = 4, .ext = "flp" },
	{	.name = "glTF Binary Format",
		.magic = "glTF", .len = 4, .ext = "glb", .mime = "model/gltf-binary" },
	{	.name = "GIMP Project",
		.magic = "gimp xcf ", .len = 9, .ext = "xcf", .mime = "image/xcf" },
	{	.name = "Microsoft Compound File Format",
		.magic = "\xD0\xCF\x11\xE0\xA1\xB1\x1A\xE1", .len = 8, .ext = "doc" },
	{	.name = "Photoshop Document",
		.magic = "8BPS", .len = 4, .ext = "psd", .mime = "image/vnd.adobe.photoshop" },
	{	.name = "Portable Document Format",
		.magic = "%PDF-", .len = 5, .ext = "pdf", .mime = "application/pdf" },
	{	.name = "Quake 2 Model",
		.magic = "IDP2\x08\x00\x00\x00", .len = 8, .ext = ".md2" },
	{	.name = "Rich Text",
		.magic = "{\x5Crtf1", .len = 6, .ext = "rtf", .mime = "application/rtf" },
	// Executable Formats
	{	.name = "ELF Binary",
		.magic = "\x7F" "ELF", .len = 4, .ext = "bin", .getinfo = elf_printer, .mime = "application/x-executable" },
	{	.name = "Windows Portable Executable (EXE)",
		.magic = "MZPE\x00\x00", .len = 6, .ext = "exe", .mime = "application/vnd.microsoft.portable-executable" },
	{	.name = "Java Class file",
		.magic = "\xFE\xCA\xBE\xBA", .len = 4, .ext = "class", .mime = "application/x-java-class" },
	{	.name = "Lua Bytecode",
		.magic = "\x1BLua", .len = 4, .ext = "luac", .mime = "application/x-lua-bytecode" },
	{	.name = "MachO Binary, 32-bit x86",
		.magic = "\xCE\xFA\xED\xFE\x07\x00\x00\x00", .len = 8, .ext = NULL, .mime = MIME_APPLICATION_GENERIC },
	{	.name = "MachO Binary, 64-bit x86",
		.magic = "\xCF\xFA\xED\xFE\x07\x00\x00\x00", .len = 8, .ext = NULL, .mime = MIME_APPLICATION_GENERIC },
	{	.name = "MachO Binary (64-bit ARM)",
		.magic = "\xCF\xFA\xED\xFE\x0C\x00\x00\x00", .len = 8, .ext = NULL, .mime = MIME_APPLICATION_GENERIC },
	{	.name = "PlayStation Package",
		.magic = "\x7F\x50\x4B\x47\x80\x00", .len = 6, .ext = "pkg" },
	{	.name = "Portable Executable Binary",
		.magic = "\x4D\x5A", .len = 2, .ext = "exe", .mime = "application/vnd.microsoft.portable-executable" },
	{	.name = "WebAssembly Binary",
		.magic = "\x00asm", .len = 4, .ext = "wasm", .mime = "application/wasm" },
	// Archive Formats
	{	.name = "BZip Archive",
		.magic = "BZh", .len = 3, .ext = "bz2", .mime = "application/x-bzip2" },
	{	.name = "CPIO Archive",
		.magic = "\x30\x37\x30\x37\x30", .len = 5, .ext = "cpio", .mime = "application/x-cpio" },
	{	.name = "Debian Linux package",
		.magic = "!<arch>\x0A", .len = 8, .ext = "deb", .mime = "application/vnd.debian.binary-package" },
	{	.name = "GZIP Archive",
		.magic = "\x1F\x8B\x08", .len = 3, .ext = "gz", .mime = "application/gzip" },
	{	.name = "LZIP Archive",
		.magic = "LZIP", .len = 4, .ext = "lz", .mime = "application/lzip" },
	{	.name = "Quake PACK Archive",
		.magic = "PACK", .len = 4, .ext = "pak" },
	{	.name = "Quake WAD Archive", // https://github.com/id-Software/Quake/tree/master/WinQuake
		.magic = "WAD2", .len = 4, .ext = "wad" },
	{	.name = "RAR Archive",
		.magic = "\x52\x61\x72\x21\x1A", .len = 5, .ext = "rar", .mime = "application/vnd.rar" },
	{	.name = "RedHat RPM Linux Package",
		.magic = "\x8E\xAD\xE8\x01\x00\x00\x00\x00", .len = 8, .ext = "rpm", .mime = "application/x-rpm" },
	{	.name = "Tar Archive",
		.magic = "ustar", .len = 5, .ext = "tar", .mime = "application/x-tar" },
	{	.name = "eXtensible ARchive",
		.magic = "xar!", .len = 4, .ext = "xar", .mime = "application/x-xar" },
	{	.name = "XZ Archive",
		.magic = "\xFD\x37\x7A\x58\x5A\x00", .len = 6, .ext = "xz", .mime = "application/x-xz" },
	{	.name = "ZIM Web Archive",
		.magic = "\x5A\x49\x4D\x04", .len = 4, .ext = "zim" },
	{	.name = "ZIP Archive",
		.magic = "PK", .len = 2, .ext = "zip", .mime = "application/zip" },
	{	.name = "7-Zip Archive",
		.magic = "7z\xBC\xAF\x27\x1C", .len = 6, .ext = "7z", .mime = "application/x-7z-compressed" },
	// Device Image Formats
	/*{	.name = "Compressed ISO Image",
		.magic = "IsZ!", .len = 4, .ext = "isz" }, // https://en.wikipedia.org/wiki/UltraISO#ISZ_format */
	{	.name = "Apple Disk Image",
		.magic = "koly\x04\x00\x00\x00", .len = 8, .ext = "dmg", .mime = "application/x-apple-diskimage" },
	{	.name = "ISO9660 CD Image",
		.magic = "CD001", .len = 5, .off = 0x8001, .ext = "iso", .mime = "application/x-iso9660-image" },
	{	.name = "qcow File Format",
		.magic = "QFI", .len = 3, .ext = "qcow", .mime = "application/x-qemu-disk" },
};

#endif
