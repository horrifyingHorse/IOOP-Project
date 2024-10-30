#ifndef CAR_H
#define CAR_H

#include <climits>
#include <string>
#include <vector>

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

class SafetyFeatures {
 protected:
  bool hasAirbags;
  bool hasABS;  // Anti Lock Braking System
  bool hasESC;  // Electronic Stability Control
  bool hasRearviewCam;
  bool hasParkingSensors;

  int airbags;

 public:
  SafetyFeatures()
      : hasAirbags(false),
        hasABS(false),
        hasESC(false),
        hasRearviewCam(false),
        hasParkingSensors(false),
        airbags(0) {}

  SafetyFeatures(bool hasAirbags, bool hasABS, bool hasESC, bool hasRearviewCam,
                 bool hasParkingSensors, int airbags)
      : hasAirbags(hasAirbags),
        hasABS(hasABS),
        hasESC(hasESC),
        hasRearviewCam(hasRearviewCam),
        hasParkingSensors(hasParkingSensors),
        airbags(airbags) {}

  friend class CarVariant;
};

class ComfortFeatures {
 protected:
  bool hasAirCondition;
  bool hasPowerWindows;
  bool hasPowerLocks;
  bool hasKeylessEntry;

  int airCondition;
  int powerWnidows;
  int powerLocks;

 public:
  ComfortFeatures()
      : hasAirCondition(false),
        hasPowerWindows(false),
        hasPowerLocks(false),
        hasKeylessEntry(false),
        airCondition(0),
        powerWnidows(0),
        powerLocks(0) {}

  ComfortFeatures(bool hasAirCondition, bool hasPowerWindows,
                  bool hasPowerLocks, bool hasKeylessEntry, int airCondition,
                  int powerWindows, int powerLocks)
      : hasAirCondition(hasAirCondition),
        hasPowerWindows(hasPowerWindows),
        hasPowerLocks(hasPowerLocks),
        hasKeylessEntry(hasKeylessEntry),
        airCondition(airCondition),
        powerWnidows(powerWindows),
        powerLocks(powerLocks) {}

  friend class CarVariant;
};

class TechnoFeatures {
 protected:
  bool hasBluetoothConn;
  bool hasUSBports;
  bool hasNavigationSys;
  bool hasAudioSystem;

 public:
  TechnoFeatures()
      : hasBluetoothConn(false),
        hasUSBports(false),
        hasNavigationSys(false),
        hasAudioSystem(false) {}

  // Overloaded constructor
  TechnoFeatures(bool hasBluetoothConn, bool hasUSBports, bool hasNavigationSys,
                 bool hasAudioSystem)
      : hasBluetoothConn(hasBluetoothConn),
        hasUSBports(hasUSBports),
        hasNavigationSys(hasNavigationSys),
        hasAudioSystem(hasAudioSystem) {}

  friend class CarVariant;
};

class BuildFeatures {
 protected:
  std::string bodyMaterial;

  double groundClearance;
  double dimensions[3];  // lxbxh

  void defaultFlags() {
    this->bodyMaterial = "Unknown";

    this->groundClearance = 0;
    this->dimensions[0] = 0;  // lxbxh
    this->dimensions[1] = 0;  // lxbxh
    this->dimensions[2] = 0;  // lxbxh
    // Rating from 0 to 5?
    //    this->suspensionQuality = 0;
    //    this->cabinNoise = 0;
    //    this->vibrationLevels = 0;
  }

 public:
  BuildFeatures() { this->defaultFlags(); }

  BuildFeatures(std::string bodyMaterial, double groundClearance,
                double dimensions[3], double suspensionQuality,
                double cabinNoise, double vibrationLevels)

      : bodyMaterial(bodyMaterial),
        groundClearance(groundClearance)
  //        suspensionQuality(suspensionQuality),
  //        cabinNoise(cabinNoise),
  //        vibrationLevels(vibrationLevels)

  {
    this->dimensions[0] = dimensions[0];
    this->dimensions[1] = dimensions[1];
    this->dimensions[2] = dimensions[2];
  }

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

 public:
  CarVariant(std::string variantName, double price)
      : variantName(variantName), price(price) {}

  CarVariant& setFuelType(Fuel& fuelType) {
    this->fuelType = fuelType;
    return *this;
  }

  CarVariant& setCarTransmission(CarTransmission& carTransmission) {
    this->carTransmission = carTransmission;
    return *this;
  }

  CarVariant& setSafetyFeatures(SafetyFeatures& safetyFeatures) {
    this->safetyFeatures = safetyFeatures;
    return *this;
  }

  CarVariant& setTechnoFeatures(TechnoFeatures& technoFeatures) {
    this->technoFeatures = technoFeatures;
    return *this;
  }

  CarVariant& setComfortFeatures(ComfortFeatures& comfortFeatures) {
    this->comfortFeatures = comfortFeatures;
    return *this;
  }

  CarVariant& setBuildFeatures(BuildFeatures& buildFeatures) {
    this->buildFeatures = buildFeatures;
    return *this;
  }

  CarVariant& pushAdditionalFeatures(std::vector<std::string>& v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
      this->additionalFeatures.push_back(*it);
    }
    return *this;
  }

  CarVariant& pushAdditionalFeatures(std::string feat) {
    this->additionalFeatures.push_back(feat);
    return *this;
  }
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
  Car(std::string modelName, std::string model, CarType carType)
      : modelName(modelName), model(model), carType(carType) {}

  ~Car() = default;

  Car& setBasePrice(double& bp) {
    this->basePrice = bp;
    return *this;
  }

  Car& setMilagePower(double m, double p) {
    this->mileage = m;
    this->power = p;
    return *this;
  }

  Car& setDoorSeatingCap(int d, int sc) {
    this->numOfDoors = d;
    this->seatingCapacity = sc;
    return *this;
  }

  Car& setFuelEngineCap(int fc, int ec) {
    this->fuelTankCapacity = fc;
    this->engineCapacity = ec;
    return *this;
  }
};

class NewCar : public Car {
 protected:
  std::vector<std::string> colors;
  std::vector<CarVariant> variants;

 public:
  NewCar& pushColors(std::string& color) {
    this->colors.push_back(color);
    return *this;
  }

  NewCar& pushColors(std::vector<std::string>& colors) {
    for (auto it = colors.begin(); it != colors.end(); ++it) {
      this->colors.push_back(*it);
    }
    return *this;
  }

  NewCar& pushVariant(CarVariant& variant) {
    this->variants.push_back(variant);
    return *this;
  }
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
