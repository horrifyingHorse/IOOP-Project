cmake_minimum_required(VERSION 3.11)
project(car-dealer LANGUAGES CXX VERSION 1.0.0)

# Specify the include directory
include_directories(include)
include_directories(dependencies/include include)

# Specify the source files
file(GLOB SOURCES
    src/*.cpp
)
# Specify the library directory
link_directories(dependencies/lib)

# Define the executable
add_executable(car-dealer src/main.cpp)

# Link against the FTXUI static library
target_link_libraries(car-dealer
  PRIVATE ftxui-screen
  PRIVATE ftxui-dom
  PRIVATE ftxui-component
)
