#ifndef IMAGE_PIXEL_H
#define IMAGE_PIXEL_H

#include <fstream>

struct Pixel {
  unsigned char red{};
  unsigned char green{};
  unsigned char blue{};
  std::iostream::pos_type pos;

  Pixel() = default;
  ~Pixel() = default;

  Pixel(const unsigned char *red, const unsigned char *green, const unsigned char *blue, std::fstream::pos_type pos);
};

#endif
