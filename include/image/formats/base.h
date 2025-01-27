#ifndef IMAGE_FORMATS_BASE_H
#define IMAGE_FORMATS_BASE_H

#include <filesystem>
#include <fstream>
#include <string>

#include "image/pixel.h"

class BaseImageFactory {
 private:
  int pixelOffset = 0;

  virtual auto getPixel() -> Pixel * { return nullptr; }
  virtual auto getResolution() -> std::string { return ""; }
  virtual auto updatePixel(Pixel *pixel) -> void {};
  virtual auto retrievePixelOffset() -> void { pixelOffset = 0; }

 protected:
  std::fstream fileStream;

  auto writeMessage(const std::string &message) -> void;
  auto readMessage() -> std::string;
  static auto getEncryptedMessage(const std::string &message) -> std::string;
  static auto getDecryptedMessage(const std::string &encryptedMessage) -> std::string;

 public:
  explicit BaseImageFactory(std::fstream &fileStream) : fileStream(std::move(fileStream)) {}

  virtual ~BaseImageFactory() = default;

  virtual auto encrypt(const std::string &message) -> void {}
  virtual auto decode() -> std::string { return ""; }
  virtual auto check(const std::string &message) -> bool { return true; }
  virtual auto information(const std::filesystem::path &path) -> void;
};

#endif
