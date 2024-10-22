#ifndef CAR_H
#define CAR_H

#include <string>
#include <vector>

enum class Fuel { PETROL, DIESEL, CNG, BIFUEL, ELECTRIC };
enum class CarTransmission { MANUAL, SEMIAUTOMATIC, AUTOMATIC };
enum class CarType {
  COMPACTSUV,
  CONVERTIBLE,
  HATCHBACK,
  JEEP,
  LIMOUSINE,
  LUXURYCAR,
  SEDAN,
  SPORTS,
  SUV,
};

class CarVariant {
 protected:
  std::string variantName;

  double price;

  std::vector<Fuel> fuelType;
  std::vector<CarTransmission> carTransmission;  // Gear Type

  std::vector<std::string> features;
};

class Car {
 protected:
  std::string modelName;
  std::string model;

  double basePrice;
  double mileage;
  double power;  // in bhp?

  int fuelTankCapacity;
  int seatingCapacity;
  int engineCapacity;  // in cc

  CarType carType;  // Car Classification

  // bool available;

  std::vector<std::string> colors;
  std::vector<CarVariant> variants;

  Car(std::string modelName, std::string model, CarType carType);
};

#endif  // !CAR_H
