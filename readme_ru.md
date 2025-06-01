# PDF2Images

PDF2Images это утилита, которая позволяет извлекать из PDF документа отдельные изображения и текст.

## Установка

Для установки необходимо предварительно установить библиотеку poppler (libpoppler-dev). Сделать это можно с помощью следующей команды:

```bash
apt install libpoppler-dev
```

После установки библиотеки, склонируйте репозиторий с помощью одного из следующих наборов команд:

```bash
git clone --recursive https://github.com/valmat/pdf2images
cd pdf2images
```
или
```bash
git clone https://github.com/valmat/pdf2images
cd pdf2images
git submodule update --init --recursive
```

Далее, перейдите в каталог src и скомпилируйте проект:

```bash
cd src
make release
```
Если вам нужна отладочная сборка, используйте следующую команду:
```bash
cd src
make -j
```

## Использование

Вот как использовать утилиты:

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
        Quiet mode (don't use progressbar)
```

Вы можете указать входной файл, каталог вывода, формат изображения, первую страницу для рендеринга, ограничение страниц для рендеринга, разрешение X и Y, DPI для вывода и опцию для рендеринга в черно-белом формате.


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
