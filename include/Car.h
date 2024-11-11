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
  friend class SearchResultRender;
  friend class RenderVariant;
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
  friend class SearchResultRender;
  friend class RenderVariant;
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
  friend class SearchResultRender;
  friend class RenderVariant;
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
  friend class SearchResultRender;
  friend class RenderVariant;
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
  friend class SecondHandCar;
  friend class SearchResultRender;
  friend class RenderVariant;

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
// Virtual? - Yes
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

  static std::string readFile(std::ifstream& f, std::string& line);

 public:
  friend class CarSearchEngine;
  friend class SearchResultRender;

  Car(std::string modelName, std::string model, CarType carType);
  virtual ~Car() = default;

  Car& setBasePrice(double& bp);
  Car& setMilagePower(double m, double p);
  Car& setDoorSeatingCap(int d, int sc);
  Car& setFuelEngineCap(int fc, int ec);
  bool isValid();
  void display() const;
};

class NewCar : public Car {
 protected:
  std::vector<std::string> colors;
  std::vector<CarVariant> variants;

 public:
  friend class CarSearchEngine;
  friend class SearchResultRender;

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
  CarVariant* variant;

  int yearsUsed;

 public:
  friend class CarSearchEngine;
  friend class SearchResultRender;

  SecondHandCar(Car& c);

  SecondHandCar& pushColors(std::string& color);
  SecondHandCar& pushVariant(CarVariant& variant);
  SecondHandCar& setCarInfo(std::string owner, int yearsUsed,
                            std::string colors);

  bool isValid();
  void display();

  static std::vector<SecondHandCar>* loadFromDB();
  static bool storeIntoDB(SecondHandCar* brandNewCar);
};

#endif  // !CAR_H
