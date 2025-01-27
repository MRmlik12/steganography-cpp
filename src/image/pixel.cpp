#include "image/pixel.h"

Pixel::Pixel(const unsigned char *red, const unsigned char *green, const unsigned char *blue,
             std::iostream::pos_type pos) : red(*red), green(*green), blue(*blue), pos(pos) {}
