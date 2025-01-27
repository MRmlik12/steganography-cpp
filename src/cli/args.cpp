#include "cli/args.h"

#include <map>

auto CliArgs::getParameters() -> std::map<std::string, std::function<void(bool)>> {
  return {{"-c", std::bind(&CliArgs::setCheck, this, std::placeholders::_1)},
          {"--check", std::bind(&CliArgs::setCheck, this, std::placeholders::_1)},
          {"-d", std::bind(&CliArgs::setDecrypt, this, std::placeholders::_1)},
          {"--decrypt", std::bind(&CliArgs::setDecrypt, this, std::placeholders::_1)},
          {"-e", std::bind(&CliArgs::setEncrypt, this, std::placeholders::_1)},
          {"--encrypt", std::bind(&CliArgs::setEncrypt, this, std::placeholders::_1)},
          {"-i", std::bind(&CliArgs::setInfo, this, std::placeholders::_1)},
          {"--info", std::bind(&CliArgs::setInfo, this, std::placeholders::_1)},
          {"-h", std::bind(&CliArgs::setHelp, this, std::placeholders::_1)},
          {"--help", std::bind(&CliArgs::setHelp, this, std::placeholders::_1)}};
};

auto CliArgs::needsDisplayHelp() const -> bool { return help; }

auto CliArgs::needsEncrypt() const -> bool { return encrypt; }

auto CliArgs::needsDecrypt() const -> bool { return decrypt; }

auto CliArgs::needsCheck() const -> bool { return check; }

auto CliArgs::getMessage() const -> std::string { return message; }

auto CliArgs::getPath() const -> std::filesystem::path { return path; }

auto CliArgs::setInfo(const bool state) -> void { info = state; }

auto CliArgs::setEncrypt(const bool state) -> void { encrypt = state; }

auto CliArgs::setDecrypt(const bool state) -> void { decrypt = state; }

auto CliArgs::setCheck(const bool state) -> void { check = state; }

auto CliArgs::setHelp(const bool state) -> void { help = state; }

auto CliArgs::needsInformation() const -> bool { return info; }

auto CliArgs::parse(const char *args[]) -> CliArgs * {
  const auto cliArgs = new CliArgs();

  auto parameters = cliArgs->getParameters();

  if (args[1] == nullptr) {
    cliArgs->setHelp(true);
    return cliArgs;
  }

  if (parameters.contains(args[1])) {
    parameters[args[1]](true);
  }

  if (cliArgs->encrypt || cliArgs->check || cliArgs->decrypt || cliArgs->info) {
    if (args[2] == nullptr) {
      throw std::invalid_argument("Brak ścieżki do pliku");
    }

    cliArgs->path = args[2];
  }

  if (cliArgs->encrypt || cliArgs->check) {
    if (args[3] == nullptr) {
      throw std::invalid_argument("Brak wiadomości do zaszyfrowania");
    }

    cliArgs->message = args[3];
  }

  return cliArgs;
}
