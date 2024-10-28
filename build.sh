#!/bin/sh

buildOnly=false

if [ $# -ge 1 ]; then
  if [ "$1" = "-b" ]; then
    buildOnly=true
  else
    echo "unknown flag $1"
    exit 1
  fi
fi

if [ -e ./build ]; then
  echo "found ./build directory;"
else
  echo "creating ./build directory;"
  mkdir ./build
fi

if dpkg -s cmake >/dev/null 2>&1; then
  echo 'found cmake to build;'
else
  echo "to build this project you need to install cmake"
  sudo apt install cmake
  # sudo apt-get install cmake
  echo "--------------------------"
  echo "cmake installed to build;"
fi

cd ./build/
cmake ..
if [ $? -eq 1 ]; then
  echo "quit building due to error;"
  exit 1
fi

make
if [ $? -eq 1 ]; then
  echo "quit building due to error;"
  exit 1
fi

cd ..
echo "build complete"
echo "--------------------------"

if ! $buildOnly; then
  echo "Executing binary


  "
  ./build/car-dealer
fi
