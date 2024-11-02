#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "../include/Car.h"
#include "../include/UI.h"

int main() {
  std::vector<NewCar> inventoryNewCar;

  while (1) {
    int option = mainMenu();

    switch (option) {
      case 0:
        inventoryNewCar.push_back(regCar());
        break;

      case 1:
        for (auto item : inventoryNewCar) {
          item.display();
        }
        break;

      default:
        exit(1);
        break;
    }
    std::cin.clear();
    fflush(stdin);
    char c = getchar();
  }

  return 0;
}
