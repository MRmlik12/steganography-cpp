#include "file/helpers.h"

#include <algorithm>
#include <cstring>

#include "consts.h"
#include "fmt/base.h"

auto getFileSizeInMB(const std::filesystem::path &path) -> double {
  return static_cast<double>(file_size(path)) / 1024 / 1024;
}

auto getLastModifiedDateTime(const std::filesystem::path &path) -> std::string {
  const auto fileTime = last_write_time(path);
  const auto systemTimePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
      fileTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
  const auto lastModifiedDateTime = std::chrono::system_clock::to_time_t(systemTimePoint);

  return std::ctime(&lastModifiedDateTime);
}

auto getExtensionSupportedByProgram(const std::filesystem::path &path) -> bool {
  const auto extension = path.extension().string();

  return std::ranges::any_of(SUPPORTED_FILES,
                             [extension](const auto format) { return std::strcmp(format, extension.c_str()); });
}

auto verifyFilePermissions(const std::filesystem::path &path, const FilePermissions permission) -> bool {
  try {
    const auto filePermissions = status(path).permissions();
    switch (permission) {
      case READ:
        return (filePermissions & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
      case WRITE:
        return (filePermissions & std::filesystem::perms::owner_write) != std::filesystem::perms::none;
      case READ_WRITE:
        return (filePermissions & std::filesystem::perms::owner_read) != std::filesystem::perms::none &&
               (filePermissions & std::filesystem::perms::owner_write) != std::filesystem::perms::none;
      default:
        return false;
    }
  } catch (const std::filesystem::filesystem_error &e) {
    fmt::println("Nie można pobrać uprawnień pliku: {}", e.what());
    return false;
  }
}
