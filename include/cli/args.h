#ifndef CLI_ARGS_H
#define CLI_ARGS_H

#include <filesystem>
#include <functional>
#include <map>

class CliArgs {
 private:
  bool info;
  bool encrypt;
  bool decrypt;
  bool check;
  bool help;

  std::string path;
  std::string message;

  auto setInfo(bool state) -> void;

  auto setEncrypt(bool state) -> void;

  auto setDecrypt(bool state) -> void;

  auto setCheck(bool state) -> void;

  auto setHelp(bool state) -> void;

  auto getParameters() -> std::map<std::string, std::function<void(bool)>>;

 public:
  CliArgs() = default;

  ~CliArgs() = delete;

  auto static parse(const char *args[]) -> CliArgs *;

  auto needsInformation() const -> bool;

  auto needsDisplayHelp() const -> bool;

  auto needsEncrypt() const -> bool;

  auto needsDecrypt() const -> bool;

  auto needsCheck() const -> bool;

  auto getMessage() const -> std::string;

  auto getPath() const -> std::filesystem::path;
};

#endif
