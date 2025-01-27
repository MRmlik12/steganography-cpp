#ifndef CLI_HELPERS_H
#define CLI_HELPERS_H

#include "cli/args.h"

auto printHelp() -> void;
auto tryCreateCliArgs(const char *argv[]) -> CliArgs*;

#endif
