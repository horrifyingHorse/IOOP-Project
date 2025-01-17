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
      case 0:  // Customer
        customerProfile(inventoryNewCar, inventorySHCar);
        break;

      case 1:  // Employee
        employeeProfile(inventoryNewCar, inventorySHCar);
        break;

      case 2:  // Manager
        managerProfile(inventoryNewCar, inventorySHCar);
        break;

      default:
        return 0;
        break;
    }
  }

  return 0;
}
