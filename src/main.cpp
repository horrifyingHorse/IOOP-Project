#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "../include/Car.h"
#include "../include/UI.h"

int main() {
  std::vector<NewCar> inventoryNewCar;
  std::vector<SecondHandCar> inventorySHCar;

  std::vector<NewCar>* inventoryPtr = NewCar::loadFromDB();
  std::vector<SecondHandCar>* inventorySHPtr = SecondHandCar::loadFromDB();

  if (inventoryPtr != nullptr) {
    inventoryNewCar = *inventoryPtr;
  }

  if (inventorySHPtr != nullptr) {
    inventorySHCar = *inventorySHPtr;
  }

  while (1) {
    int usrProfile = profileSelect();
    switch (usrProfile) {
      case 0:
        customerProfile(inventoryNewCar, inventorySHCar);
        break;

      case 1:
        employeeProfile(inventoryNewCar, inventorySHCar);
        break;

      default:
        return 0;
        break;
    }
  }

  return 0;
}
