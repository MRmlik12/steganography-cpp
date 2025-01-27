![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![GitHub repo size](https://img.shields.io/github/repo-size/MRmlik12/steganography-cpp?style=for-the-badge)
![GitHub](https://img.shields.io/github/license/MRmlik12/steganography-cpp?style=for-the-badge)

# Steganography in C++

CLI tool to hide and extract text in images using LSB technique. Created for PJC (Programming in C/C++) course at PJAIT university.

## Features

- Hide text in image in .bmp and .ppm format
- Extract text from image in .bmp and .ppm format
- Check if the text can be hidden in the image
- File information (size, format, last modified date, resolution)

## Requirements

* CMake 3.29 or higher
* GCC or clang compiler with C++20 support
* Make

## Building

```bash
$ cmake . .
$ cmake --build .
```

## Usage

```bash
$ ./steganography_cli 
Użycie: ./steganography-cli [opcje]
-h                                                      Wyświetla dostępne opcje programu
-i / --include "<ścieżka_do_pliku>"                     Wyświetla informacje o pliku
-c / --check   "<ścieżka_do_pliku>" "<wiadomość>"       Sprawdza, czy jest możliwe ukrycie wiadomości w pliku
-e / --encrypt "<ścieżka_do_pliku>" "<wiadomość>"       Ukrywa wiadomość w pliku graficznym (Wspierane formaty to .bmp i .ppm)
-d / --decrypt "<ścieżka_do_pliku>"                     Odszyfrowuje plik (Wspierane formaty to .bmp i .ppm)
```