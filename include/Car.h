#ifndef CAR_H
#define CAR_H

#include <climits>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "utils.h"

enum class Fuel { PETROL, DIESEL, CNG, BIFUEL, ELECTRIC };
enum class CarTransmission { MANUAL, SEMIAUTOMATIC, AUTOMATIC };
enum class CarType {
  COMPACTSUV,
  CONVERTIBLE,
  DEFAULT,
  HATCHBACK,
  JEEP,
  LIMOUSINE,
  LUXURYCAR,
  SEDAN,
  SPORTS,
  SUV,
};

std::string fuelToString(Fuel fuel);
std::string transmissionToString(CarTransmission transmission);
std::string carTypeToString(CarType type);

Fuel stringToFuel(const std::string& fuelStr);
CarTransmission stringToTransmission(const std::string& transmissionStr);
CarType stringToCarType(std::string type);

class CarSearchEngine;

class SafetyFeatures {
 protected:
  bool hasAirbags;
  bool hasABS;  // Anti Lock Braking System
  bool hasESC;  // Electronic Stability Control
  bool hasRearviewCam;
  bool hasParkingSensors;

  int airbags;

 public:
  SafetyFeatures();
  SafetyFeatures(bool hasAirbags, bool hasABS, bool hasESC, bool hasRearviewCam,
                 bool hasParkingSensors, int airbags);

  void display() const;

  friend class CarVariant;
};

class ComfortFeatures {
 protected:
  bool hasAirCondition;
  bool hasPowerWindows;
  bool hasPowerLocks;
  bool hasKeylessEntry;

  int airCondition;
  // int powerWnidows;
  // int powerLocks;

 public:
  ComfortFeatures();
  ComfortFeatures(bool hasAirCondition, bool hasPowerWindows,
                  bool hasPowerLocks, bool hasKeylessEntry, int airCondition
                  // , int powerWindows, int powerLocks
  );

  void display() const;

  friend class CarVariant;
};

class TechnoFeatures {
 protected:
  bool hasBluetoothConn;
  bool hasUSBports;
  bool hasNavigationSys;
  bool hasAudioSystem;

 public:
  TechnoFeatures();
  TechnoFeatures(bool hasBluetoothConn, bool hasUSBports, bool hasNavigationSys,
                 bool hasAudioSystem);

  void display() const;

  friend class CarVariant;
};

class BuildFeatures {
 protected:
  std::string bodyMaterial;

  double groundClearance;
  double dimensions[3];  // lxbxh

 public:
  BuildFeatures();

  BuildFeatures(
      std::string bodyMaterial, double groundClearance, double dimensions[3]
      //, double suspensionQuality, double cabinNoise, double vibrationLevels
  );

  bool isValid();

  void display() const;

  friend class CarVariant;
};

class CarVariant {
 protected:
  std::string variantName;

  double price;

  // Performance
  Fuel fuelType;
  // fuel efficiency?
  CarTransmission carTransmission;  // Gear Type

  SafetyFeatures safetyFeatures;
  TechnoFeatures technoFeatures;
  ComfortFeatures comfortFeatures;
  BuildFeatures buildFeatures;

  std::vector<std::string> additionalFeatures;

  static bool loadIntoDB(std::ofstream& f, CarVariant& cv);

 public:
  friend class NewCar;
  void display();

  bool isValid();

  CarVariant(std::string variantName, double price);

  CarVariant& setFuelType(Fuel& fuelType);
  CarVariant& setCarTransmission(CarTransmission& carTransmission);
  CarVariant& setSafetyFeatures(SafetyFeatures& safetyFeatures);
  CarVariant& setTechnoFeatures(TechnoFeatures& technoFeatures);
  CarVariant& setComfortFeatures(ComfortFeatures& comfortFeatures);
  CarVariant& setBuildFeatures(BuildFeatures& buildFeatures);

  CarVariant& pushAdditionalFeatures(std::vector<std::string>& v);
  CarVariant& pushAdditionalFeatures(std::string feat);
};

// Abstract? - No
class Car {
 protected:
  std::string modelName;
  std::string model;

  double basePrice;
  double mileage;
  double power;  // in bhp?

  int fuelTankCapacity;
  int seatingCapacity;
  int numOfDoors;
  int engineCapacity;  // in cc

  CarType carType;  // Car Classification

  // bool available;

 public:
  Car(std::string modelName, std::string model, CarType carType);

  Car& setBasePrice(double& bp);
  Car& setMilagePower(double m, double p);
  Car& setDoorSeatingCap(int d, int sc);
  Car& setFuelEngineCap(int fc, int ec);
  bool isValid();
  void display() const;
};

class NewCar : public Car {
 private:
  static std::string readFile(std::ifstream& f, std::string& line);

 protected:
  std::vector<std::string> colors;
  std::vector<CarVariant> variants;

 public:
  friend class CarSearchEngine;
  void display();

  NewCar(Car& c);

  NewCar& pushColors(std::string color);
  NewCar& pushColors(std::vector<std::string>& colors);
  NewCar& pushVariant(CarVariant& variant);

  static std::vector<NewCar>* loadFromDB();
  static bool storeIntoDB(NewCar* brandNewCar);
};

class SecondHandCar : public Car {
 protected:
  std::string colors;
  std::string prevOwner;
  CarVariant* variants;

  int yearsUsed;

 public:
  SecondHandCar(std::string modelName, std::string model, CarType carType)
      : Car(modelName, model, carType),
        colors("Default"),
        variants(nullptr),
        prevOwner("Default"),
        yearsUsed(INT_MAX)
  {}

  SecondHandCar& pushColors(std::string& color) {
    this->colors = color;
    return *this;
  }

  SecondHandCar& setCarInfo(std::string owner, int yearsUsed,
                            std::string colors, CarVariant* variants) {
    this->prevOwner = owner;
    this->yearsUsed = yearsUsed;
    this->colors = colors;
    this->variants = variants;  // Shallow Copy
    return *this;
  }
};

#endif  // !CAR_H
