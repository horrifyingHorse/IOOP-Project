#include "../include/Humans.h"
#include "../include/UI.h"

void managerProfile(std::vector<NewCar>& inventoryNewCar,
                    std::vector<SecondHandCar>& inventorySHCar) {
  Manager arpit;
  if (!managerLogin(arpit)) return;
  while (1) {
    int option = mainMenuManager();
    switch (option) {
      case 0: {
        addEmployee(arpit);
        break;
      }

      case 1: {
        removeEmployee(arpit);
        break;
      }

      case 2: {
        managerSalesView(arpit);
        break;
      }

      default:
        return;
        break;
    }
  }
}

void employeeProfile(std::vector<NewCar>& inventoryNewCar,
                     std::vector<SecondHandCar>& inventorySHCar) {
  while (1) {
    int option = mainMenuEmployee();
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

      case 1: {
        SecondHandCar* aCar = regSecondHandCar();
        if (aCar == nullptr) break;

        if (SecondHandCar::storeIntoDB(aCar))
          std::cout << "Stored in db\n";
        else
          std::cout << "Newly Reg Car was not stored in db\n";

        inventorySHCar.push_back(*aCar);

        break;
      }

      default:
        return;
        break;
    }
  }
}

void customerProfile(std::vector<NewCar>& inventoryNewCar,
                     std::vector<SecondHandCar>& inventorySHCar) {
  searchCars(inventoryNewCar, inventorySHCar);
}
