#include "image/formats/ppm.h"

#include "consts.h"
#include "fmt/base.h"
#include "fmt/format.h"

auto PpmImageFactory::getPixel() -> Pixel * {
  if (fileStream.tellg() > pixelOffset) {
    fileStream.seekg(3, std::ios::cur);
  }

  const auto pos = fileStream.tellg();
  const auto red = new unsigned char;
  const auto green = new unsigned char;
  const auto blue = new unsigned char;

  fileStream.read(reinterpret_cast<char *>(red), 1);
  fileStream.read(reinterpret_cast<char *>(green), 1);
  fileStream.read(reinterpret_cast<char *>(blue), 1);

  return new Pixel{red, green, blue, pos};
}

auto PpmImageFactory::updatePixel(Pixel *pixel) -> void {
  fileStream.seekg(pixel->pos, std::ios::beg);

  fileStream.write(reinterpret_cast<const char *>(&pixel->red), 1);
  fileStream.write(reinterpret_cast<const char *>(&pixel->green), 1);
  fileStream.write(reinterpret_cast<const char *>(&pixel->blue), 1);
}

auto PpmImageFactory::getResolution() -> std::string {
  fileStream.seekg(2, std::ios::beg);

  while (fileStream >> std::ws && fileStream.peek() == '#') {
    fileStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  int imageProps[2];
  fileStream >> imageProps[0] >> imageProps[1];

  return fmt::format("{}x{}", std::to_string(imageProps[0]), std::to_string(imageProps[1]));
}

auto PpmImageFactory::decode() -> std::string {
  fileStream.seekg(pixelOffset, std::ios::beg);

  return readMessage();
}

auto PpmImageFactory::check(const std::string &message) -> bool {
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

auto PpmImageFactory::encrypt(const std::string &message) -> void {
  fileStream.seekg(pixelOffset, std::ios::beg);

  writeMessage(message);
}

auto PpmImageFactory::retrievePixelOffset() -> void {
  fileStream.seekg(2, std::ios::beg);
  while (fileStream >> std::ws && fileStream.peek() == '#') {
    fileStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  int temp;
  fileStream >> temp >> temp >> temp;
  fileStream.ignore();

  pixelOffset = static_cast<int>(fileStream.tellg());
}
