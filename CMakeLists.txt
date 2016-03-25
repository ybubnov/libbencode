cmake_minimum_required(VERSION 2.8)

project(bencode)
enable_testing()

set(CMAKE_BUILD_TYPE Release)

include_directories(include)
include_directories(include/bencode)

# Add the testing directory.
add_subdirectory(test)

# Install the library files.
install(DIRECTORY include/bencode DESTINATION bencode)
install(FILES include/bencode.hpp DESTINATION include)
