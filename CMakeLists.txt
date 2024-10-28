cmake_minimum_required(VERSION 3.12)
project(
  car-dealer
  LANGUAGES CXX
  VERSION 1.0.0)

include_directories(dependencies/include include)

file(GLOB SOURCES src/*.cpp)

add_executable(car-dealer src/main.cpp)

find_package(ftxui REQUIRED)
target_link_libraries(car-dealer PRIVATE ftxui::screen ftxui::dom
                                         ftxui::component)
