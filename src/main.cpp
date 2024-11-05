#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "../include/Car.h"
#include "../include/UI.h"

int main() {
  std::vector<NewCar> inventoryNewCar;
  std::vector<NewCar>* inventoryPtr = NewCar::loadFromDB();

  if (inventoryPtr != nullptr) {
    inventoryNewCar = *inventoryPtr;
  }

  while (1) {
    int option = mainMenu();

    switch (option) {
      case 0: {
        NewCar* aCar = regCar();
        if (aCar == nullptr) break;

        if (NewCar::storeIntoDB(aCar))
          std::cout << "Stored in db\n";
        else
          std::cout << "Newly Reg Car was not stored in db\n";

        inventoryNewCar.push_back(*aCar);
        break;
      }

      case 1:
        // for (auto item : inventoryNewCar) {
        //   item.display();
        // }

        searchCars(inventoryNewCar);
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
