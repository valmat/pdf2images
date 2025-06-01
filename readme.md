# PDF2Images

PDF2Images is a utility that allows you to extract individual images and text from a PDF document.

## Installation

To install, you first need to install the poppler library (libpoppler-dev). This can be done using the following command:

```bash
apt install libpoppler-dev
```

After installing the library, clone the repository using one of the following sets of commands:

```bash
git clone --recursive https://github.com/valmat/pdf2images
cd pdf2images
```
or
```bash
git clone https://github.com/valmat/pdf2images
cd pdf2images
git submodule update --init --recursive
```

Next, go to the src directory and compile the project:

```bash
cd src
make release
```
If you need a debug build, use the following command:
```bash
cd src
make -j
```

## Usage

Here's how to use this utilities:

```bash
$bin/extract_imgs.bin -h
bin/extract_imgs.bin <input_file.pdf> [options]
    -h, --help
        Print help and exit
    -i, --inp, --input
        Input file
    -o, --out, --output
        Output directory (default '.')
    -e, --ext
        Pdf render images format (default 'png'. Use 'png', 'jpg', 'tiff' etc)
    -p, --pref
        Output files prefix
    -f, --from
        The first page to render (default '1')
    -l, --lim
        Pdf render pages limit (-1: no limits)
    -x, --xres
        X resolution file
    -y, --yres
        Y resolution
    -d, --dpi
        Pdf render dpi out (-1: system)
    -g, --bw, --gray
        Make black and white render (default: off)
    -q, --quiet
        Quiet mode
```

You can specify the input file, output directory, image format, the first page to render, the page limit for rendering, X and Y resolution, DPI for output, and an option for rendering in black and white format.

```bash
$ bin/extract_txts.bin -h
bin/extract_txts.bin -i <input_file.pdf> [options]
    -h, --help
        Show help information and exit.
    -i, --inp, --input
        Input PDF file (required).
    -o, --out-dir
        Output directory (default is './').
    -O, --out-file
        Output file name (if set, directory options are ignored).
    -p, --pre, --prefix
        Output file name prefix. Used only when saving files to a directory.
    -P, --post, --postfix
        Output file name postfix (default is '.txt'). Used only when saving files to a directory.
    -f, --from
        PDF: first page to extract (default is '1').
    -l, --limit
        PDF: maximum number of pages to extract (-1 means no limit).
    -q, --quiet
        Quiet mode (no progress will be shown).
    -n, --nopagebreak
        Do not add a separator between pages (works only if saving to a single output file).

```
