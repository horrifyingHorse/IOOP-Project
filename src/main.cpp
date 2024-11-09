#include <cmath>
#include <cstdio>
#include <cstdlib>
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
    int usrProfile = profileSelect();
    switch (usrProfile) {
      case 0:
        customerProfile(inventoryNewCar);
        break;

      case 1:
        employeeProfile(inventoryNewCar);
        break;

      default:
        return 0;
        break;
    }
  }

  return 0;
}
