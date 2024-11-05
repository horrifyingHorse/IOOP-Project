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
    } else {
      this->airbags = airbags;
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
    if (this->bodyMaterial == "Unknown") {
      std::cerr << "Wrong Body";
      return false;
    }

    if (this->groundClearance <= 0) {
      std::cerr << "Wrong GC";
      return false;
    }
    for (auto dimension : this->dimensions) {
      if (dimension <= 0) {
        std::cerr << "Wrong Dim";
        return false;
      }
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

  static inline bool loadIntoDB(std::ofstream& f, CarVariant& cv) {
    f << cv.price << "\n";
    f << cv.variantName << "\n";
    f << fuelToString(cv.fuelType) << "\n";
    f << transmissionToString(cv.carTransmission) << "\n";

    f << cv.safetyFeatures.airbags << "\n";
    f << cv.safetyFeatures.hasParkingSensors << "\n";
    f << cv.safetyFeatures.hasRearviewCam << "\n";
    f << cv.safetyFeatures.hasESC << "\n";
    f << cv.safetyFeatures.hasABS << "\n";
    f << cv.safetyFeatures.hasAirbags << "\n";

    f << cv.comfortFeatures.airCondition << "\n";
    f << cv.comfortFeatures.hasKeylessEntry << "\n";
    f << cv.comfortFeatures.hasPowerLocks << "\n";
    f << cv.comfortFeatures.hasPowerWindows << "\n";
    f << cv.comfortFeatures.hasAirCondition << "\n";

    f << cv.technoFeatures.hasAudioSystem << "\n";
    f << cv.technoFeatures.hasNavigationSys << "\n";
    f << cv.technoFeatures.hasUSBports << "\n";
    f << cv.technoFeatures.hasBluetoothConn << "\n";

    for (auto dimension : cv.buildFeatures.dimensions) {
      f << dimension << ",";
    }
    f << "\n";
    f << cv.buildFeatures.groundClearance << "\n";
    f << cv.buildFeatures.bodyMaterial << "\n";

    for (auto feature : cv.additionalFeatures) {
      f << feature << ",";
    }
    f << "\n";

    return true;
  }

 public:
  friend class NewCar;
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
 private:
  static inline std::string readFile(std::ifstream& f, std::string& line) {
    if (f.eof()) return "";
    std::getline(f, line);

    return line;
  }

 protected:
  std::vector<std::string> colors;
  std::vector<CarVariant> variants;

 public:
  friend class CarSearchEngine;
  void display() {
    Car::display();

    std::cout << "Available Colors: ";
    for (auto color : colors) {
      std::cout << color << "\t";
    }
    std::cout << "\n";

    for (auto variant : variants) {
      variant.display();
      std::cout << "\n";
    }
  }

  NewCar(Car& c) : Car(c) {
    colors = {};
    variants = {};
  }

  NewCar& pushColors(std::string color) {
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

  static inline std::vector<NewCar>* loadFromDB() {
    namespace fs = std::filesystem;
    std::vector<NewCar>* v = nullptr;

    fs::path dirPath = "./db/";

    if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
      std::cout << "Directory exists: " << dirPath << std::endl;

      for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
          std::ifstream file(entry.path());
          if (!file) {
            std::cerr << "Could not open file: " << entry.path() << std::endl;
            continue;
          }

          std::cout << "Reading file: " << entry.path() << std::endl;
          std::string line;

          Car tempCar(NewCar::readFile(file, line),
                      NewCar::readFile(file, line),
                      stringToCarType(NewCar::readFile(file, line)));
          double bp = utils::stod(NewCar::readFile(file, line));
          double m = utils::stod(NewCar::readFile(file, line));
          double p = utils::stod(NewCar::readFile(file, line));
          int d = utils::stoi(NewCar::readFile(file, line));
          int sc = utils::stoi(NewCar::readFile(file, line));
          int fc = utils::stoi(NewCar::readFile(file, line));
          int ec = utils::stoi(NewCar::readFile(file, line));

          tempCar.setBasePrice(bp)
              .setMilagePower(m, p)
              .setDoorSeatingCap(d, sc)
              .setFuelEngineCap(fc, ec);
          if (!tempCar.isValid()) {
            std::cerr << "Corrupt Data in " << entry.path()
                      << ": (Invalid Car Object)\n";
            tempCar.display();
            continue;
          }

          NewCar* brandNewCar = new NewCar(tempCar);

          NewCar::readFile(file, line);
          while (line != "" && line.find(",") != std::string::npos) {
            brandNewCar->pushColors(line.substr(0, line.find(",")));
            line = line.substr(line.find(",") + 1);
          }
          if (line != "") brandNewCar->pushColors(line);

          bool errFlag = false;
          while (!file.eof()) {
            CarVariant* cv =
                new CarVariant(NewCar::readFile(file, line),
                               utils::stod(NewCar::readFile(file, line)));
            Fuel ft = stringToFuel(NewCar::readFile(file, line));
            CarTransmission ct =
                stringToTransmission(NewCar::readFile(file, line));
            SafetyFeatures sf(utils::stob(NewCar::readFile(file, line)),
                              utils::stob(NewCar::readFile(file, line)),
                              utils::stob(NewCar::readFile(file, line)),
                              utils::stob(NewCar::readFile(file, line)),
                              utils::stob(NewCar::readFile(file, line)),
                              utils::stoi(NewCar::readFile(file, line)));

            ComfortFeatures cf(utils::stob(NewCar::readFile(file, line)),
                               utils::stob(NewCar::readFile(file, line)),
                               utils::stob(NewCar::readFile(file, line)),
                               utils::stob(NewCar::readFile(file, line)),
                               utils::stoi(NewCar::readFile(file, line)));

            TechnoFeatures tf(utils::stob(NewCar::readFile(file, line)),
                              utils::stob(NewCar::readFile(file, line)),
                              utils::stob(NewCar::readFile(file, line)),
                              utils::stob(NewCar::readFile(file, line)));

            double dims[3];
            NewCar::readFile(file, line);
            if (line.find(",") == std::string::npos) {
              if (file.eof()) break;
              std::cerr << "Corrupt Data in " << entry.path()
                        << ": (Invalid BuildFeatures Object)\n";
              errFlag = true;
              break;
            }
            dims[0] = utils::stod(line.substr(0, line.find(",")));
            line = line.substr(line.find(",") + 1);
            dims[1] = utils::stod(line.substr(0, line.find(",")));
            line = line.substr(line.find(",") + 1);
            dims[2] = utils::stod(line.substr(0));

            BuildFeatures bf(NewCar::readFile(file, line),
                             utils::stod(NewCar::readFile(file, line)), dims);

            if (!bf.isValid()) {
              std::cerr << "Corrupt Data in " << entry.path()
                        << ": (Invalid BuildFeatures Object)\n";
              errFlag = true;
              break;
            }

            cv->setFuelType(ft)
                .setCarTransmission(ct)
                .setSafetyFeatures(sf)
                .setComfortFeatures(cf)
                .setTechnoFeatures(tf)
                .setBuildFeatures(bf);

            if (!cv->isValid()) {
              std::cerr << "Corrupt Data in " << entry.path()
                        << ": (Invalid CarVariant Object)\n";
              errFlag = true;
              break;
            }

            NewCar::readFile(file, line);
            while (line != "" && line.find(",") != std::string::npos) {
              cv->pushAdditionalFeatures(line.substr(0, line.find(",")));
              line = line.substr(line.find(",") + 1);
            }
            if (line != "") cv->pushAdditionalFeatures(line);

            brandNewCar->pushVariant(*cv);
          }
          if (errFlag) continue;
          if (v == nullptr) {
            v = new std::vector<NewCar>;
          }
          v->push_back(*brandNewCar);
        }
      }
    } else {
      std::cerr << "No DataBase directory found in PWD: " << dirPath
                << std::endl;
    }

    return v;
  }

  static inline bool storeIntoDB(NewCar* brandNewCar) {
    namespace fs = std::filesystem;
    fs::path dirPath = "./db/";
    std::string fname =
        brandNewCar->modelName + "_" + brandNewCar->model + ".txt";
    fs::path filePath = dirPath / fname;

    if (!fs::exists(dirPath)) {
      if (fs::create_directory(dirPath)) {
        std::cout << "Directory created: " << dirPath << std::endl;
      } else {
        std::cerr << "Failed to create directory: " << dirPath << std::endl;
        return 1;
      }
    }

    std::ofstream file(filePath);
    if (!file.is_open()) {
      std::cerr << "Failed to create file: " << filePath << std::endl;
      return false;
    }

    file << carTypeToString(brandNewCar->carType) << "\n";
    file << brandNewCar->model << "\n";
    file << brandNewCar->modelName << "\n";
    file << brandNewCar->basePrice << "\n";
    file << brandNewCar->mileage << "\n";
    file << brandNewCar->power << "\n";
    file << brandNewCar->numOfDoors << "\n";
    file << brandNewCar->seatingCapacity << "\n";
    file << brandNewCar->fuelTankCapacity << "\n";
    file << brandNewCar->engineCapacity << "\n";
    for (auto color : brandNewCar->colors) {
      file << color << ",";
    }
    file << "\n";

    for (auto variant : brandNewCar->variants) {
      if (!CarVariant::loadIntoDB(file, variant)) {
        return false;
      }
    }

    return true;
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
