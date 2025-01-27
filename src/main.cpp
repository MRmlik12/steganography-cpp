#include <fstream>

#include "cli/args.h"
#include "cli/helpers.h"
#include "file/helpers.h"
#include "fmt/base.h"
#include "image/formats/base.h"
#include "image/formats/ppm.h"

template<typename T = BaseImageFactory>
auto startAction(const CliArgs *args, std::unique_ptr<T> imageFactory, const std::filesystem::path &filePath,
                 const std::string &message) -> void {
  if (args->needsDecrypt()) {
    auto decryptedMessage = imageFactory->decode();
    fmt::println("Ukryta wiadomość: {}", decryptedMessage);
  } else if (args->needsInformation()) {
    imageFactory->information(filePath);
  } else if (args->needsCheck()) {
    if (!imageFactory->check(message)) {
      fmt::println("Wiadomość jest za długa");
      return;
    }

    fmt::println("Podana wiadomość zmieści się w podanym pliku");
  } else if (args->needsEncrypt() && verifyFilePermissions(filePath, READ_WRITE)) {
    imageFactory->encrypt(message);

    fmt::println("Wiadomość została ukryta w pliku");
  }
}

auto main(int argc, const char *argv[]) -> int {
  const auto args = tryCreateCliArgs(argv);

  if (!args) {
    return -1;
  }

  if (args->needsDisplayHelp()) {
    printHelp();
    return 0;
  }

  const auto path = args->getPath();

  if (!verifyFilePermissions(path, READ)) {
    fmt::println("Plik nie posiada uprawnień do odczytu");
    return -1;
  }

  std::fstream fileStream(path, std::ios::in | std::ios::out | std::ios::binary);
  if (!fileStream.is_open()) {
    fmt::println("Nie można otworzyć pliku");

    return -1;
  }

  auto imageFactory = getImageProvider(path, fileStream);
  if (!imageFactory) {
    return -1;
  }

  startAction(args, std::move(imageFactory), path, args->getMessage());

  return 0;
}
