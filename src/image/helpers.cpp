#include "image/helpers.h"

#include <fstream>

#include "consts.h"
#include "fmt/base.h"
#include "image/formats/bmp.h"
#include "image/formats/ppm.h"

auto isPpmFile(std::fstream &fileStream) -> bool {
  const auto header = new unsigned char[2];
  fileStream.read(reinterpret_cast<char *>(header), 2);

  if (header[0] != PPM_HEADERS[0] && header[1] != PPM_HEADERS[1]) {
    delete[] header;
    fileStream.seekg(0, std::ios::beg);

    return false;
  }

  delete[] header;

  fileStream.seekg(0, std::ios::beg);

  return true;
}

auto isBmpFile(std::fstream &fileStream) -> bool {
  const auto headers = new unsigned char[2];
  fileStream.read(reinterpret_cast<char *>(headers), 2);

  if (headers[0] != BMP_HEADERS[0] && headers[1] != BMP_HEADERS[1]) {
    delete[] headers;
    fileStream.seekg(0, std::ios::beg);

    return false;
  }

  delete[] headers;

  fileStream.seekg(0, std::ios::beg);

  return true;
}

auto getImageProvider(const std::filesystem::path &path, std::fstream &fileStream)
    -> std::unique_ptr<BaseImageFactory> {
  std::unique_ptr<BaseImageFactory> imageFactory;
  try {
    const auto extension = path.extension().string();
    if (extension == SUPPORTED_FILES[1] && isPpmFile(fileStream)) {
      imageFactory = std::make_unique<PpmImageFactory>(fileStream);
    } else if (extension == SUPPORTED_FILES[0] && isBmpFile(fileStream)) {
      imageFactory = std::make_unique<BmpImageFactory>(fileStream);
    } else {
      fmt::println("Nieobsługiwany format pliku");
      return nullptr;
    }
  } catch (std::invalid_argument &e) {
    fmt::println("{}", e.what());

    return nullptr;
  }

  return imageFactory;
}
