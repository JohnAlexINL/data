#ifndef MAGIC_H
#define MAGIC_H
#include <stdio.h>
#include <string.h>

	// Allows overriding the default printer function for certain types
typedef void *type_parser(void *type, char *in);
void parser_default(void *type, char *in);
int parse_magic(char *in);
long parse_size(char *in);
long get_size(FILE *f);
int parse_scale(long in);

typedef struct
	{ char * name; char * magic; char * ext; int off; int len; type_parser *printer; }
	filetype_t;

extern filetype_t * type;

#define magic_table_size ( sizeof(magic_table) / sizeof(magic_table[0]) )
filetype_t magic_table [] = {
	// Easily-identifiable Text Files
	{	.name = "Shebang script",
		.magic = "#!", .len = 2 },
	{	.name = "SSH/Other Key File",
		.magic = "-----BEGIN", .len = 10, .ext = "key" },
	{	.name = "XML Document",
		.magic = "<?xml", .len = 4, .ext = "xml" },
	// Raster Image Formats
		// TODO: JPEG Subformats
	{ 	.name = "PNG Image",
		.magic = "\x89PNG\x0D\x0A\x1A\xA0", .len = 8, .ext = "png" },
	{	.name = "JPEG Image",
		.magic = "\xFF\xD8\xFF", .len = 3, .ext = "jpeg" },
	{	.name = "Quite-OK Image Format",
		.magic = "qoif", .len = 4, .ext = "qoi" },
	{	.name = "GIF Image (version 87)",
		.magic = "GIF87a", .len = 4, .ext = "gif" },
	{	.name = "GIF Image (version 89)",
		.magic = "GIF89a", .len = 4, .ext = "gif" },
	{	.name = "Bitmap Image",
		.magic = "BM", .ext = "bmp", .len = 2 },
	{	.name = "Tagged Image File (Little-Endian)",
		.magic = "\x49\x49\x2A\x00",
		.len = 4, .ext = "tiff" },
	{	.name = "Tagged Image File (Big-Endian)",
		.magic = "\x4D\x4D\x00\x2A",
		.len = 4, .ext = "tiff" },
	{	.name = "WebP Container Format",
		.magic = "WEBP", .len = 4, .off = 8, .ext = "webp" },
	// Vector Image Formats
	// Audio and Video Containers
	{	.name = "Waveform Audio",
		.magic = "WAVE", .len = 4, .off = 8, .ext = "wav" },
	{	.name = "Audio Video Interleave",
		.magic = "AVI\x20", .len = 4, .off = 8, .ext = "avi" },
	{	.name = "Tagged MP3 Audio",
		.magic = "ID3", .len = 3, .ext = "mp3" },
	{	.name = "MP4 Video",
		.magic = "\x66\x74\x79", .off = 4, .len = 3, .ext = "mp4" },
	{	.name = "OGG Vorbis Format",
		.magic = "OggS", .len = 4, .ext = "ogg" },
	{	.name = "Audio Interchange Format",
		.magic = "AIFF", .len = 4, .off = 4, .ext = "aiff" },
	{	.name = "Quite-OK Audio Format",
		.magic = "qoaf", .len = 4, .ext = "qoa" },
	// Other Multimedia
	{	.name = "Portable Document Format",
		.magic = "%PDF-", .len = 5, .ext = "pdf" },
	{	.name = "Blender File Format",
		.magic = "BLENDER", .len = 7, .ext = "blend" },
	{	.name = "glTF Binary Format",
		.magic = "glTF", .len = 4, .ext = "glb" },
	// Executable Formats
		// TODO: MachO Format
		// TODO: ELF Format Printer, checks header for subtype information
	{	.name = "ELF Binary",
		.magic = "\x7F" "ELF", .len = 4, .ext = "bin" },
	{	.name = "Portable Executable Binary",
		.magic = "\x4D\x5A", .len = 2, .ext = "exe" },
	{	.name = "WebAssembly Binary",
		.magic = "\x00asm", .len = 4, .ext = "wasm" },
	// Archive Formats
	{	.name = "ZIP Archive",
		.magic = "\x50\x4B", .len = 2, .ext = "zip" },
	{	.name = "GZIP Archive",
		.magic = "\x1F\x8B", .len = 2, .ext = "gz" },
	{	.name = "LZIP Archive",
		.magic = "LZIP", .len = 4, .ext = "lz" },
	{	.name = "XZ Archive",
		.magic = "\xFD\x37\x7A\x58\x5A\x00", .len = 6, .ext = "xz" },
	{	.name = "7-Zip Archive",
		.magic = "7z\xBC\xAF\x27\x1C", .len = 6, .ext = "7z" },
	{	.name = "RAR Archive",
		.magic = "\x52\x61\x72\x21\x1A", .len = 5, .ext = "rar" },
	{	.name = "BZip Archive",
		.magic = "BZh", .len = 3, .ext = "bz2" },
	{	.name = "CPIO Archive",
		.magic = "\x30\x37\x30\x37\x30", .len = 5, .ext = "cpio" },
	{	.name = "Debian Linux package",
		.magic = "!<arch>\x0A", .len = 8, .ext = "deb" },
	// Device Image Formats
	{	.name = "qcow File Format",
		.magic = "QFI", .len = 3, .ext = "qcow" },
	{	.name = "ISO9660 CD Image",
		.magic = "CD001", .len = 5, .ext = "iso" },
	{	.name = "Compressed ISO Image",
		.magic = "IsZ!", .len = 4, .ext = "isz" },
};

#endif
