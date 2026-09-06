# Data
## Data is a lightweight replacement for file from coreutils.

![demo](demo/demo.gif)

![GitHub Views](https://img.shields.io/github/watchers/unistd-h/data?label=Watchers&style=for-the-badge)
![GitHub stars](https://img.shields.io/github/stars/unistd-h/data?style=for-the-badge)
![GitHub Downloads](https://img.shields.io/github/downloads/unistd-h/data/total?style=for-the-badge)


[![CI](https://github.com/unistd-h/data/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/unistd-h/data/actions/workflows/c-cpp.yml)
### Usage:
```bash
data [file] #lookup file
data --help #show help
data -h #show help
data --license #show license
data -l #show license
```
### Building from source:
```bash
make #make bin
make clean #clean
make install #install into /bin/
make remove #remove from /bin/
```
### Format support:
> See [./src/magic.h](src/magic.h)

- Images:		BMP, PNG, JPEG, QOI, GIF, TIFF, WEBP
- Audio:		WAV, MP3, OGG, QOA, AIFF
- Video:		MP4, AVI
- Multimedia:	PDF, Blender, glTF
- Executables:	ELF, EXE, WebAssembly
- Archives:		ZIP, GZIP, LZIP, 7-Zip, RAR, BZip, CPIO, .deb
- Binary Data:	qcow, ISO
- Other:		XML, Shebang scripts, SSH keys
