#ifndef IMAGE_FORMATS_PPM_H
#define IMAGE_FORMATS_PPM_H

#include <fstream>
#include <string>

#include "base.h"
#include "image/helpers.h"
#include "image/pixel.h"

class PpmImageFactory final : public BaseImageFactory {
 private:
  int pixelOffset = 0;

  auto getPixel() -> Pixel * override;

  auto updatePixel(Pixel *pixel) -> void override;

  auto getResolution() -> std::string override;

  auto retrievePixelOffset() -> void override;

 public:
  explicit PpmImageFactory(std::fstream &fileStream) : BaseImageFactory(fileStream) {
    PpmImageFactory::retrievePixelOffset();
  }

  auto encrypt(const std::string &message) -> void override;

  auto decode() -> std::string override;

  auto check(const std::string &message) -> bool override;
};

#endif
