#ifndef CAR_H
#define CAR_H

#include <climits>
#include <iostream>
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

std::string fuelToString(Fuel fuel);
std::string transmissionToString(CarTransmission transmission);
std::string carTypeToString(CarType type);

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
        hasParkingSensors(hasParkingSensors) {
    if (!hasAirbags) {
      this->airbags = 0;
    }
  }

  void display() const {
    std::cout << "Car Features:" << std::endl;
    std::cout << "Has Airbags: " << (hasAirbags ? "Yes" : "No") << std::endl;
    std::cout << "Has ABS: " << (hasABS ? "Yes" : "No") << std::endl;
    std::cout << "Has ESC: " << (hasESC ? "Yes" : "No") << std::endl;
    std::cout << "Has Rearview Camera: " << (hasRearviewCam ? "Yes" : "No")
              << std::endl;
    std::cout << "Has Parking Sensors: " << (hasParkingSensors ? "Yes" : "No")
              << std::endl;
    std::cout << "Number of Airbags: " << airbags << std::endl;
  }

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
  ComfortFeatures()
      : hasAirCondition(false),
        hasPowerWindows(false),
        hasPowerLocks(false),
        hasKeylessEntry(false),
        airCondition(0)
  // ,powerWnidows(0),
  // powerLocks(0)
  {}

  ComfortFeatures(bool hasAirCondition, bool hasPowerWindows,
                  bool hasPowerLocks, bool hasKeylessEntry, int airCondition
                  // , int powerWindows, int powerLocks
                  )
      : hasAirCondition(hasAirCondition),
        hasPowerWindows(hasPowerWindows),
        hasPowerLocks(hasPowerLocks),
        hasKeylessEntry(hasKeylessEntry),
        airCondition(airCondition)
  // , powerWnidows(powerWindows), powerLocks(powerLocks)
  {
    if (!hasAirCondition) this->airCondition = 0;
    // if (!hasPowerWindows) this->powerWnidows = 0;
    // if (!hasPowerLocks) this->powerLocks = 0;
  }

  void display() const {
    std::cout << "Additional Features:" << std::endl;
    std::cout << "Has Air Conditioning: " << (hasAirCondition ? "Yes" : "No")
              << std::endl;
    std::cout << "Has Power Windows: " << (hasPowerWindows ? "Yes" : "No")
              << std::endl;
    std::cout << "Has Power Locks: " << (hasPowerLocks ? "Yes" : "No")
              << std::endl;
    std::cout << "Has Keyless Entry: " << (hasKeylessEntry ? "Yes" : "No")
              << std::endl;
    std::cout << "Air Conditioning Level: " << airCondition << std::endl;
  }

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

  void display() const {
    std::cout << "Connectivity and Entertainment Features:" << std::endl;
    std::cout << "Has Bluetooth Connection: "
              << (hasBluetoothConn ? "Yes" : "No") << std::endl;
    std::cout << "Has USB Ports: " << (hasUSBports ? "Yes" : "No") << std::endl;
    std::cout << "Has Navigation System: " << (hasNavigationSys ? "Yes" : "No")
              << std::endl;
    std::cout << "Has Audio System: " << (hasAudioSystem ? "Yes" : "No")
              << std::endl;
  }

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

  BuildFeatures(
      std::string bodyMaterial, double groundClearance, double dimensions[3]
      //, double suspensionQuality, double cabinNoise, double vibrationLevels
      )

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

  bool isValid() {
    if (this->bodyMaterial == "Unknown") return false;
    if (this->groundClearance <= 0) return false;
    for (auto dimension : this->dimensions) {
      if (dimension <= 0) return false;
    }

    return true;
  }

  void display() const {
    std::cout << "Vehicle Specifications:" << std::endl;
    std::cout << "Body Material: " << bodyMaterial << std::endl;
    std::cout << "Ground Clearance: " << groundClearance << " mm" << std::endl;
    std::cout << "Dimensions (L x W x H): " << dimensions[0] << " x "
              << dimensions[1] << " x " << dimensions[2] << " m" << std::endl;
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

  std::string trim(std::string& s) {
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    return s;
  }

 public:
  void display() {
    std::cout << "Variant Name: " << variantName << "\n";
    std::cout << "Variant price: " << price << "\n";
    std::cout << "Fuel Type: " << fuelToString(fuelType) << "\n";
    std::cout << "Transmission: " << transmissionToString(carTransmission)
              << "\n";
    safetyFeatures.display();
    technoFeatures.display();
    comfortFeatures.display();
    buildFeatures.display();
  }

  bool isValid() {
    if (trim(variantName) == "") return false;
    if (price <= 0) return false;

    return true;
  }

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
  std::string trim(std::string& s) {
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    return s;
  }

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
      : modelName(modelName),
        model(model),
        carType(carType),
        basePrice(0),
        mileage(0),
        power(0),
        fuelTankCapacity(0),
        seatingCapacity(0),
        numOfDoors(0),
        engineCapacity(0) {}

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

  bool isValid() {
    if (trim(model) == "" || trim(modelName) == "") return false;
    if (carType == CarType::DEFAULT) return false;
    if (basePrice * mileage * power <= 0) return false;
    if (seatingCapacity * numOfDoors * engineCapacity <= 0) return false;
    if (fuelTankCapacity < 0) return false;

    return true;
  }

  void display() const {
    std::cout << "Car Model Details:" << std::endl;
    std::cout << "Model Name: " << modelName << std::endl;
    std::cout << "Model: " << model << std::endl;
    std::cout << "Base Price: $" << basePrice << std::endl;
    std::cout << "Mileage: " << mileage << " km/l" << std::endl;
    std::cout << "Power: " << power << " bhp" << std::endl;
    std::cout << "Fuel Tank Capacity: " << fuelTankCapacity << " liters"
              << std::endl;
    std::cout << "Seating Capacity: " << seatingCapacity << " persons"
              << std::endl;
    std::cout << "Number of Doors: " << numOfDoors << std::endl;
    std::cout << "Engine Capacity: " << engineCapacity << " cc" << std::endl;
    std::cout << "Car Type: " << carTypeToString(carType) << std::endl;
  }
};

class NewCar : public Car {
 protected:
  std::vector<std::string> colors;
  std::vector<CarVariant> variants;

 public:
  void display() {
    Car::display();
    for (auto variant : variants) {
      variant.display();
      std::cout << "\n";
    }
  }

  NewCar(Car& c) : Car(c) {
    colors = {};
    variants = {};
  }

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
