#include "image/formats/bmp.h"

#include <fstream>
#include <ios>
#include <istream>
#include <string>

#include "consts.h"
#include "fmt/base.h"
#include "fmt/format.h"

auto BmpImageFactory::getResolution() -> std::string {
  fileStream.seekg(18, std::ios::beg);

  auto width = 0;
  auto height = 0;

  fileStream.read(reinterpret_cast<char *>(&width), sizeof(width));
  fileStream.read(reinterpret_cast<char *>(&height), sizeof(height));

  return fmt::format("{}x{}", width, height);
}

auto BmpImageFactory::retrievePixelOffset() -> void {
  fileStream.seekg(10, std::ios::beg);

  const auto offset = new unsigned char;
  fileStream.read(reinterpret_cast<char *>(offset), 4);

  pixelOffset = std::stoi(std::to_string(*offset));

  delete offset;
}

auto BmpImageFactory::getPixel() -> Pixel * {
  if (fileStream.tellg() > pixelOffset) {
    fileStream.seekg(4, std::ios::cur);
  }

  const auto pos = fileStream.tellg();

  const auto red = new unsigned char;
  const auto green = new unsigned char;
  const auto blue = new unsigned char;

  fileStream.read(reinterpret_cast<char *>(red), 1);
  fileStream.read(reinterpret_cast<char *>(green), 1);
  fileStream.read(reinterpret_cast<char *>(blue), 1);

  fileStream.seekg(1, std::ios::cur);

  return new Pixel{red, green, blue, pos};
}

auto BmpImageFactory::updatePixel(Pixel *pixel) -> void {
  fileStream.seekg(pixel->pos, std::ios::beg);

  fileStream.write(reinterpret_cast<const char *>(&pixel->red), 1);
  fileStream.write(reinterpret_cast<const char *>(&pixel->green), 1);
  fileStream.write(reinterpret_cast<const char *>(&pixel->blue), 1);
  fileStream.seekg(1, std::ios::cur);
}

auto BmpImageFactory::decode() -> std::string {
  fileStream.seekg(pixelOffset, std::ios::beg);

  auto binaryMessage = readMessage();

  return binaryMessage;
}

auto BmpImageFactory::check(const std::string &message) -> bool {
  fileStream.seekg(pixelOffset, std::ios::beg);
  const auto sizeBegin = fileStream.tellg();

  fileStream.seekg(0, std::ios::end);
  const auto sizeEnd = fileStream.tellg();

  const auto size = sizeEnd - sizeBegin;

  const auto binaryMessage = getEncryptedMessage(message);
  if (size < binaryMessage.length() + MAX_MESSAGE_SIZE * 8) {
    return false;
  }

  return true;
}

auto BmpImageFactory::encrypt(const std::string &message) -> void {
  fileStream.seekg(pixelOffset, std::ios::beg);

  writeMessage(message);
}
