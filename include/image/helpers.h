#ifndef IMAGE_HELPERS_H
#define IMAGE_HELPERS_H

#include <fstream>

#include "image/formats/base.h"

auto isPpmFile(std::fstream &fileStream) -> bool;
auto isBmpFile(std::fstream &fileStream) -> bool;
auto getImageProvider(const std::filesystem::path &path, std::fstream &fileStream) -> std::unique_ptr<BaseImageFactory>;

#endif
