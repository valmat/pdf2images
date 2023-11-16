# PDF2Images

PDF2Images is a utility that allows you to extract individual images from a PDF document.

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
git submodule update
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

Here's how to use this utility:

```bash
$bin/extract_imgs.bin -h
bin/extract_imgs.bin [options]
    -h, --help
        Print help and exit
    -i, --inp, --input
        Input file
    -o, --out, --output
        Output directory (default '.')
    -e, --ext
        Pdf render images format (default 'png')
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
```

You can specify the input file, output directory, image format, the first page to render, the page limit for rendering, X and Y resolution, DPI for output, and an option for rendering in black and white format.
