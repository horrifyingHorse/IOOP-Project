cmake_minimum_required(VERSION 3.12)

project(
  car-dealer
  LANGUAGES CXX
  VERSION 1.0.0)

if(WIN32)
  set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/Dependencies/win/")
  include_directories(Dependencies/win/include include)
elseif(UNIX)
  set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/Dependencies/linux/")
  include_directories(Dependencies/linux/include include)
endif()

file(GLOB SOURCES src/*.cpp)

add_executable(car-dealer src/main.cpp)

find_package(ftxui REQUIRED)
target_link_libraries(car-dealer PRIVATE ftxui::screen ftxui::dom
                                         ftxui::component)
