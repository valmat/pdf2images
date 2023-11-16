# PDF2Images

PDF2Images это утилита, которая позволяет извлекать из PDF документа отдельные изображения.

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

Вот как использовать эту утилиту:

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
        Pdf render images format (default 'png'. Use 'png', 'jpg', 'tiff' etc)
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

Вы можете указать входной файл, каталог вывода, формат изображения, первую страницу для рендеринга, ограничение страниц для рендеринга, разрешение X и Y, DPI для вывода и опцию для рендеринга в черно-белом формате.