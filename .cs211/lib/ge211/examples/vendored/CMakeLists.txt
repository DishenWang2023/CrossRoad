# See README.md

cmake_minimum_required(VERSION 3.13)
project(ge211_vendored_example CXX)

add_subdirectory(3rdparty/ge211 EXCLUDE_FROM_ALL)

add_executable(fw src/fw.cxx)
target_link_libraries(fw ge211)
set_target_properties(fw PROPERTIES
        CXX_STANDARD            14
        CXX_STANDARD_REQUIRED   On
        CXX_EXTENSIONS          OFF)

