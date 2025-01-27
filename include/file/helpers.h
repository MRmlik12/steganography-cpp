#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H

#include <filesystem>

enum FilePermissions { READ, WRITE, READ_WRITE };

auto getFileSizeInMB(const std::filesystem::path &path) -> double;
auto getLastModifiedDateTime(const std::filesystem::path &path) -> std::string;
auto getExtensionSupportedByProgram(const std::filesystem::path &path) -> bool;
auto verifyFilePermissions(const std::filesystem::path &path, FilePermissions permission) -> bool;

#endif
