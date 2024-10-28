#include <iostream>
using namespace std;

// abstract
class Car {
 protected:
  std::string color;
  std::string name;
  double price;

 public:
  Car(std::string c, std::string n, double price)
      : color(c), name(n), price(price) {}

  virtual Car& addColor(std::string c) = 0;

  friend ostream& operator<<(ostream&, Car*);
};

class NewCar : public Car {
 private:
  bool hasVariants;

 public:
  NewCar(Car& c, std::string color, string name, double price): Car(c) {
    this->color = color;
    this->name = name;
    this->price = price;
    this->hasVariants = true;
  }

  NewCar& addColor(std::string c) {
    this->color = c;
    return *this;
  }
};

ostream& operator<<(ostream& s, Car* c) {
  s << c->name;
  s << c->color;

  return s;
}

int main() {
  Car* myCar = new NewCar(string("Red"), string("mini sex"), 2500000);
  myCar->addColor(string("Cyan"));

  cout << myCar;

  return 0;
}
