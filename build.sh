#!/bin/bash
buildOnly=false
osid=$(cat /etc/os-release | awk -F = '{if(NR == 3){print $2}}')
pkgmng="apt install"

echo "$osid detected;"
if [[ $osid == "arch" ]]; then
  pkgmng="pacman -S"
fi
echo $pkgmng

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

if which cmake >/dev/null 2>&1; then
  echo 'found cmake to build;'
else
  echo "to build this project you need to install cmake;"
  sudo $pkgmng cmake
  if [ $? -eq 1 ]; then
    echo "quit building; cmake couldn't be installed;"
    exit 1
  fi
  echo "cmake installed to build;"
fi

cd ./build/
cmake ..
if [ $? -eq 1 ]; then
  echo "quit building due to cmake error;"
  exit 1
fi

make -j8
if [ $? -eq 1 ]; then
  echo "quit building due to make error;"
  exit 1
fi

cd ..
echo "build complete"
echo "--------------------------"

if ! $buildOnly; then
  echo "Executing binary


  "
  # clear
  ./build/car-dealer
fi
