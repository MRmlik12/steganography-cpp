#include "cli/helpers.h"

#include "fmt/base.h"

auto printHelp() -> void {
  fmt::println("Użycie: ./steganography-cli [opcje]");
  fmt::println("-h\t\t\t\t\t\t\tWyświetla dostępne opcje programu");
  fmt::println("-i / --include \"<ścieżka_do_pliku>\"\t\t\tWyświetla informacje o pliku");
  fmt::println(
      "-c / --check   \"<ścieżka_do_pliku>\" \"<wiadomość>\"\tSprawdza, czy jest możliwe ukrycie wiadomości w pliku");
  fmt::println(
      "-e / --encrypt \"<ścieżka_do_pliku>\" \"<wiadomość>\"\tUkrywa wiadomość w pliku graficznym (Wspierane formaty "
      "to .bmp i .ppm)");
  fmt::println("-d / --decrypt \"<ścieżka_do_pliku>\"\t\t\tOdszyfrowuje plik (Wspierane formaty to .bmp i .ppm)");
}

auto tryCreateCliArgs(const char *argv[]) -> CliArgs* {
  try {
    const auto args = CliArgs::parse(argv);

    return args;
  } catch (const std::invalid_argument &e) {
    fmt::println("{}", e.what());

    return nullptr;
  }
}
