#include <cstdlib>
#include <iostream>

#include "./mainMenu.cpp"

int main() {
  int option = mainMenu();

  std::cout << option;

  switch (option) {
    case 1:
      exit(1);
      break;
  }

  return 0;
}
