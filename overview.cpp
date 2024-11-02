#include <iostream>
#include <string>
#include <vector>
using namespace std;

class car {
 private:
  string make;
  string model;
  double price;
  bool available;

 public:
  car(string make, string model, double price) {
    this->make = make;
    this->model = model;
    this->price = price;
    this->available = true;
  }

  void displaydetails() const {
    cout << "Make: " << make << endl;
    cout << "Model: " << model << endl;
    cout << "Price: $" << price << endl;
    cout << "Available: " << (available ? "Yes" : "No") << endl;
  }

  bool isAvailable() const { return available; }

  void markasSold() { available = false; }

  string getmodel() const { return model; }

  double getprice() const { return price; }
};

class customer {
 private:
  string name;
  double budget;

 public:
  customer(string name, double budget) {
    this->name = name;
    this->budget = budget;
  }

  string getname() const { return name; }

  double getbudget() const { return budget; }

  bool canAfford(double price) const { return price <= budget; }
};

class Salesperson {
 private:
  string name;
  int salescount;

 public:
  Salesperson(string name) {
    this->name = name;
    salescount = 0;
  }

  string getname() const { return name; }

  void sellcar(customer &customer, car &car) {
    if (car.isAvailable() && customer.canAfford(car.getprice())) {
      cout << customer.getname() << " bought a " << car.getmodel() << " from "
           << name << endl;
      car.markasSold();
      salescount++;
    } else {
      cout << customer.getname() << " cannot buy a " << car.getmodel() << endl;
    }
  }

  void displaysales() const {
    cout << "Salesperson: " << name << " has sold " << salescount << " cars."
         << endl;
  }
};

class dealership {
 private:
  vector<car> inventory;
  vector<Salesperson> salespeople;

 public:
  void addcar(const car &car) { inventory.push_back(car); }

  void addsalesperson(const Salesperson &salesperson) {
    salespeople.push_back(salesperson);
  }

  void showinventory() const {
    cout << "Car Inventory:\n";
    for (const auto &car : inventory) {
      car.displaydetails();
      cout << "--------------------\n";
    }
  }

  car *findcarmymodel(const string &model) {
    for (auto &car : inventory) {
      if (car.getmodel() == model && car.isAvailable()) {
        return &car;
      }
    }
    return nullptr;
  }

  Salesperson *getsalespersonbyname(const string &name) {
    for (auto &salesperson : salespeople) {
      if (salesperson.getname() == name) {
        return &salesperson;
      }
    }
    return nullptr;
  }
};

int main() {
  dealership d1;
  d1.addcar(car("Ford", "Mustang", 90000));
  d1.addcar(car("Dodge", "Challenger", 85000));
  d1.addcar(car("Chevrolet", "Camaro", 95000));
  d1.addsalesperson(Salesperson("Arnold"));
  d1.addsalesperson(Salesperson("Bobby"));
  d1.showinventory();
  customer customer("Mark Cuban", 95000);
  car *selectedCar = d1.findcarmymodel("Camaro");
  Salesperson *selectedSalesperson = d1.getsalespersonbyname("Arnold");
  if (selectedCar && selectedSalesperson) {
    selectedSalesperson->sellcar(customer, *selectedCar);
  } else {
    cout << "Car or salesperson not found!" << endl;
  }
  d1.showinventory();
  selectedSalesperson->displaysales();
  return 0;
}
