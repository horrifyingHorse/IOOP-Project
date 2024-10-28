#include <cstdlib>
#include <iostream>

#include "./mainMenu.cpp"
#include "./regCar.cpp"

int main() {
  int option = mainMenu();

  switch (option) {
    case 0:
      regCar();
      break;

    case 1:
      exit(1);
      break;
  }

  return 0;
}
