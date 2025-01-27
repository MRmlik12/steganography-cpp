#include "image/formats/base.h"

#include <bitset>

#include "consts.h"
#include "file/helpers.h"
#include "fmt/base.h"

auto BaseImageFactory::writeMessage(const std::string &message) -> void {
  const auto binaryMessage = getEncryptedMessage(message);

  for (auto i = 0; i < MAX_MESSAGE_SIZE; i += 3) {
    const auto pixel = getPixel();

    pixel->red = pixel->red & 0xFE | binaryMessage.length() >> i & 1;
    pixel->green = pixel->green & 0xFE | binaryMessage.length() >> i + 1 & 1;
    pixel->blue = pixel->blue & 0xFE | binaryMessage.length() >> i + 2 & 1;

    updatePixel(pixel);

    delete pixel;
  }

  auto writtenBits = 0;
  const auto messageLength = binaryMessage.length();
  while (writtenBits < messageLength) {
    const auto pixel = getPixel();

    if (writtenBits < messageLength) {
      pixel->red = pixel->red & 0xFE | binaryMessage[writtenBits] - '0';
      writtenBits++;
    }

    if (writtenBits < messageLength) {
      pixel->green = pixel->green & 0xFE | binaryMessage[writtenBits] - '0';
      writtenBits++;
    }

    if (writtenBits < messageLength) {
      pixel->blue = pixel->blue & 0xFE | binaryMessage[writtenBits] - '0';
      writtenBits++;
    }

    updatePixel(pixel);

    delete pixel;
  }
}

auto BaseImageFactory::readMessage() -> std::string {
  size_t messageLength = 0;
  for (auto i = 0; i < MAX_MESSAGE_SIZE; i += 3) {
    const auto pixel = getPixel();

    messageLength |= (pixel->red & 1) << i;
    messageLength |= (pixel->green & 1) << i + 1;
    messageLength |= (pixel->blue & 1) << i + 2;

    delete pixel;
  }

  auto readBytes = 0;
  std::string binaryMessage;

  while (readBytes < messageLength) {
    const auto pixel = getPixel();

    binaryMessage += pixel->red & 0x01 ? '1' : '0';
    binaryMessage += pixel->green & 0x01 ? '1' : '0';
    binaryMessage += pixel->blue & 0x01 ? '1' : '0';

    readBytes += 3;

    delete pixel;
  }

  return getDecryptedMessage(binaryMessage);
}

auto BaseImageFactory::getEncryptedMessage(const std::string &message) -> std::string {
  std::string binaryMessage;
  for (const char i: message) {
    binaryMessage += std::bitset<8>(static_cast<unsigned char>(i)).to_string();
  }

  return binaryMessage;
}

auto BaseImageFactory::getDecryptedMessage(const std::string &encryptedMessage) -> std::string {
  std::string message;

  try {
    for (auto i = 0; i < encryptedMessage.size(); i += 8) {
      auto bytes = encryptedMessage.substr(i, 8);
      const auto ch = static_cast<char>(std::stoi(bytes, nullptr, 2));
      message.push_back(ch);
    }
  } catch (std::invalid_argument &e) {
    fmt::println("{}", e.what());
  } catch (std::out_of_range &e) {
    fmt::println("{}", e.what());
  }

  return message;
}

auto BaseImageFactory::information(const std::filesystem::path &path) -> void {
  fmt::println("Nazwa pliku: {}", path.filename().string());
  fmt::println("Wspierany rozszerzenie przez program: {}", getExtensionSupportedByProgram(path) ? "Tak" : "Nie");
  fmt::println("Uprawniony do zapisu: {}", verifyFilePermissions(path, WRITE) ? "Tak" : "Nie");
  fmt::println("Uprawniony do odczytu: {}", verifyFilePermissions(path, READ) ? "Tak" : "Nie");
  fmt::println("Rozmiar pliku: {:.2f} MB", getFileSizeInMB(path));
  fmt::print("Data ostatniej modyfikacji: {}", getLastModifiedDateTime(path));
  fmt::println("Rozdzielczość: {}", getResolution());
}
