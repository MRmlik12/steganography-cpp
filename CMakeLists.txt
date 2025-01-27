cmake_minimum_required(VERSION 3.29)
project(steganography_cli)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 11.0.2)
FetchContent_MakeAvailable(fmt)

include_directories(include)
add_executable(steganography_cli src/main.cpp
        include/image/formats/ppm.h
        include/image/formats/bmp.h
        include/image/formats/base.h
        src/image/formats/base.cpp
        include/image/pixel.h
        src/image/formats/ppm.cpp
        src/image/formats/bmp.cpp
        src/image/pixel.cpp
        src/image/formats/base.cpp
        include/image/helpers.h
        src/image/helpers.cpp
        include/file/helpers.h
        src/file/helpers.cpp
        include/cli/args.h
        src/cli/args.cpp
        include/cli/helpers.h
        src/cli/helpers.cpp
)
target_link_libraries(steganography_cli fmt::fmt)
