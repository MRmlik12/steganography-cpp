#ifndef CONSTS_H
#define CONSTS_H

constexpr char *SUPPORTED_FILES[2] = {".bmp", ".ppm"};
constexpr unsigned char BMP_HEADERS[2] = {0x42, 0x4D};
constexpr unsigned char PPM_HEADERS[2] = {0x50, 0x36};
constexpr char MAX_MESSAGE_SIZE = 64;

#endif
