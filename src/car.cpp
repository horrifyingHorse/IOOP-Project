#include "../include/Car.h"

#include <iomanip>

std::string fuelToString(Fuel fuel) {
  switch (fuel) {
    case Fuel::PETROL:
      return "Petrol";
    case Fuel::DIESEL:
      return "Diesel";
    case Fuel::CNG:
      return "CNG";
    case Fuel::BIFUEL:
      return "Bi-Fuel";
    case Fuel::ELECTRIC:
      return "Electric";
    default:
      return "Unknown";
  }
}

Fuel stringToFuel(const std::string& fuelStr) {
  if (fuelStr == "Petrol") {
    return Fuel::PETROL;
  } else if (fuelStr == "Diesel") {
    return Fuel::DIESEL;
  } else if (fuelStr == "CNG") {
    return Fuel::CNG;
  } else if (fuelStr == "Bi-Fuel") {
    return Fuel::BIFUEL;
  } else if (fuelStr == "Electric") {
    return Fuel::ELECTRIC;
  } else {
    return Fuel::PETROL;  // Default case for unrecognized strings
  }
}

std::string transmissionToString(CarTransmission transmission) {
  switch (transmission) {
    case CarTransmission::MANUAL:
      return "Manual";
    case CarTransmission::SEMIAUTOMATIC:
      return "Semi-Automatic";
    case CarTransmission::AUTOMATIC:
      return "Automatic";
    default:
      return "Unknown";
  }
}

CarTransmission stringToTransmission(const std::string& transmissionStr) {
  if (transmissionStr == "Manual") {
    return CarTransmission::MANUAL;
  } else if (transmissionStr == "Semi-Automatic") {
    return CarTransmission::SEMIAUTOMATIC;
  } else if (transmissionStr == "Automatic") {
    return CarTransmission::AUTOMATIC;
  } else {
    return CarTransmission::MANUAL;  // Default case for unrecognized strings
  }
}

std::string carTypeToString(CarType type) {
  switch (type) {
    case CarType::COMPACTSUV:
      return "Compact SUV";
    case CarType::CONVERTIBLE:
      return "Convertible";
    case CarType::DEFAULT:
      return "Default";
    case CarType::HATCHBACK:
      return "Hatchback";
    case CarType::JEEP:
      return "Jeep";
    case CarType::LIMOUSINE:
      return "Limousine";
    case CarType::LUXURYCAR:
      return "Luxury Car";
    case CarType::SEDAN:
      return "Sedan";
    case CarType::SPORTS:
      return "Sports";
    case CarType::SUV:
      return "SUV";
    default:
      return "Unknown";
  }
}

CarType stringToCarType(const std::string carTypeStr) {
  if (carTypeStr == "Compact SUV") {
    return CarType::COMPACTSUV;
  } else if (carTypeStr == "Convertible") {
    return CarType::CONVERTIBLE;
  } else if (carTypeStr == "Default") {
    return CarType::DEFAULT;
  } else if (carTypeStr == "Hatchback") {
    return CarType::HATCHBACK;
  } else if (carTypeStr == "Jeep") {
    return CarType::JEEP;
  } else if (carTypeStr == "Limousine") {
    return CarType::LIMOUSINE;
  } else if (carTypeStr == "Luxury Car") {
    return CarType::LUXURYCAR;
  } else if (carTypeStr == "Sedan") {
    return CarType::SEDAN;
  } else if (carTypeStr == "Sports") {
    return CarType::SPORTS;
  } else if (carTypeStr == "SUV") {
    return CarType::SUV;
  } else {
    std::cout << "No choice as : " << carTypeStr << "\n";
    return CarType::DEFAULT;
  }
}

SafetyFeatures::SafetyFeatures()
    : hasAirbags(false),
      hasABS(false),
      hasESC(false),
      hasRearviewCam(false),
      hasParkingSensors(false),
      airbags(0) {}

SafetyFeatures::SafetyFeatures(bool hasAirbags, bool hasABS, bool hasESC,
                               bool hasRearviewCam, bool hasParkingSensors,
                               int airbags)
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

void SafetyFeatures::display() const {
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

ComfortFeatures::ComfortFeatures()
    : hasAirCondition(false),
      hasPowerWindows(false),
      hasPowerLocks(false),
      hasKeylessEntry(false),
      airCondition(0)
// ,powerWnidows(0),
// powerLocks(0)
{}

ComfortFeatures::ComfortFeatures(bool hasAirCondition, bool hasPowerWindows,
                                 bool hasPowerLocks, bool hasKeylessEntry,
                                 int airCondition
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

void ComfortFeatures::display() const {
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

TechnoFeatures::TechnoFeatures()
    : hasBluetoothConn(false),
      hasUSBports(false),
      hasNavigationSys(false),
      hasAudioSystem(false) {}

TechnoFeatures::TechnoFeatures(bool hasBluetoothConn, bool hasUSBports,
                               bool hasNavigationSys, bool hasAudioSystem)
    : hasBluetoothConn(hasBluetoothConn),
      hasUSBports(hasUSBports),
      hasNavigationSys(hasNavigationSys),
      hasAudioSystem(hasAudioSystem) {}

void TechnoFeatures::display() const {
  std::cout << "Connectivity and Entertainment Features:" << std::endl;
  std::cout << "Has Bluetooth Connection: " << (hasBluetoothConn ? "Yes" : "No")
            << std::endl;
  std::cout << "Has USB Ports: " << (hasUSBports ? "Yes" : "No") << std::endl;
  std::cout << "Has Navigation System: " << (hasNavigationSys ? "Yes" : "No")
            << std::endl;
  std::cout << "Has Audio System: " << (hasAudioSystem ? "Yes" : "No")
            << std::endl;
}

BuildFeatures::BuildFeatures() : bodyMaterial("Unknown"), groundClearance(0) {
  dimensions[0] = 0;
  dimensions[1] = 0;
  dimensions[2] = 0;
}

BuildFeatures::BuildFeatures(
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

bool BuildFeatures::isValid() {
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

void BuildFeatures::display() const {
  std::cout << "Vehicle Specifications:" << std::endl;
  std::cout << "Body Material: " << bodyMaterial << std::endl;
  std::cout << "Ground Clearance: " << groundClearance << " mm" << std::endl;
  std::cout << "Dimensions (L x W x H): " << dimensions[0] << " x "
            << dimensions[1] << " x " << dimensions[2] << " m" << std::endl;
}

bool CarVariant::loadIntoDB(std::ofstream& f, CarVariant& cv) {
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

void CarVariant::display() {
  std::cout << "Variant Name: " << variantName << "\n";
  std::cout << "Variant price: " << std::fixed << std::setprecision(2) << price
            << "\n";
  std::cout << "Fuel Type: " << fuelToString(fuelType) << "\n";
  std::cout << "Transmission: " << transmissionToString(carTransmission)
            << "\n";
  safetyFeatures.display();
  technoFeatures.display();
  comfortFeatures.display();
  buildFeatures.display();
}

std::string CarVariant::getName() { return this->variantName; }

double CarVariant::getPrice() { return this->price; }

bool CarVariant::isValid() {
  if (utils::trim(variantName) == "") return false;
  if (price <= 0) return false;

  return true;
}

CarVariant::CarVariant(std::string variantName, double price)
    : variantName(variantName), price(price) {}

CarVariant& CarVariant::setFuelType(Fuel& fuelType) {
  this->fuelType = fuelType;
  return *this;
}

CarVariant& CarVariant::setCarTransmission(CarTransmission& carTransmission) {
  this->carTransmission = carTransmission;
  return *this;
}

CarVariant& CarVariant::setSafetyFeatures(SafetyFeatures& safetyFeatures) {
  this->safetyFeatures = safetyFeatures;
  return *this;
}

CarVariant& CarVariant::setTechnoFeatures(TechnoFeatures& technoFeatures) {
  this->technoFeatures = technoFeatures;
  return *this;
}

CarVariant& CarVariant::setComfortFeatures(ComfortFeatures& comfortFeatures) {
  this->comfortFeatures = comfortFeatures;
  return *this;
}

CarVariant& CarVariant::setBuildFeatures(BuildFeatures& buildFeatures) {
  this->buildFeatures = buildFeatures;
  return *this;
}

CarVariant& CarVariant::pushAdditionalFeatures(std::vector<std::string>& v) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    this->additionalFeatures.push_back(*it);
  }
  return *this;
}

CarVariant& CarVariant::pushAdditionalFeatures(std::string feat) {
  this->additionalFeatures.push_back(feat);
  return *this;
}

Car::Car(std::string modelName, std::string model, CarType carType)
    : modelName(modelName),
      model(model),
      carType(carType),
      basePrice(0.0),
      mileage(0.0),
      power(0.0),
      fuelTankCapacity(0),
      seatingCapacity(0),
      numOfDoors(0),
      engineCapacity(0) {}

Car& Car::setBasePrice(double& bp) {
  this->basePrice = bp;
  return *this;
}

Car& Car::setMilagePower(double m, double p) {
  this->mileage = m;
  this->power = p;
  return *this;
}

Car& Car::setDoorSeatingCap(int d, int sc) {
  this->numOfDoors = d;
  this->seatingCapacity = sc;
  return *this;
}

Car& Car::setFuelEngineCap(int fc, int ec) {
  this->fuelTankCapacity = fc;
  this->engineCapacity = ec;
  return *this;
}

bool Car::isValid() {
  if (utils::trim(model) == "" || utils::trim(modelName) == "") return false;
  if (carType == CarType::DEFAULT) return false;
  if (basePrice * mileage * power <= 0) return false;
  if (seatingCapacity * numOfDoors * engineCapacity <= 0) return false;
  if (fuelTankCapacity < 0) return false;

  return true;
}

void Car::display() const {
  std::cout << "Car Model Details:" << std::endl;
  std::cout << "Model Name: " << modelName << std::endl;
  std::cout << "Model: " << model << std::endl;
  std::cout << "Base Price: $" << basePrice << std::endl;
  std::cout << "Mileage: " << std::fixed << std::setprecision(1) << mileage
            << " km/l" << std::endl;
  std::cout << "Power: " << power << " bhp" << std::endl;
  std::cout << "Fuel Tank Capacity: " << fuelTankCapacity << " liters"
            << std::endl;
  std::cout << "Seating Capacity: " << seatingCapacity << " persons"
            << std::endl;
  std::cout << "Number of Doors: " << numOfDoors << std::endl;
  std::cout << "Engine Capacity: " << engineCapacity << " cc" << std::endl;
  std::cout << "Car Type: " << carTypeToString(carType) << std::endl;
}

std::string Car::readFile(std::ifstream& f, std::string& line) {
  if (f.eof()) return "";
  std::getline(f, line);

  return line;
}

void NewCar::display() {
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

NewCar::NewCar(Car& c) : Car(c) {
  colors = {};
  variants = {};
}

NewCar& NewCar::pushColors(std::string color) {
  this->colors.push_back(color);
  return *this;
}

NewCar& NewCar::pushColors(std::vector<std::string>& colors) {
  for (auto it = colors.begin(); it != colors.end(); ++it) {
    this->colors.push_back(*it);
  }
  return *this;
}

NewCar& NewCar::pushVariant(CarVariant& variant) {
  this->variants.push_back(variant);
  return *this;
}

std::vector<NewCar>* NewCar::loadFromDB() {
  namespace fs = std::filesystem;
  std::vector<NewCar>* v = nullptr;

  fs::path dirPath = "./db/";

  if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
    // std::cout << "Directory exists: " << dirPath << std::endl;

    for (const auto& entry : fs::directory_iterator(dirPath)) {
      if (entry.is_regular_file() && entry.path().extension() == ".txt") {
        std::ifstream file(entry.path());
        if (!file) {
          std::cerr << "Could not open file: " << entry.path() << std::endl;
          continue;
        }

        // std::cout << "Reading file: " << entry.path() << std::endl;
        std::string line;

        Car tempCar(Car::readFile(file, line), NewCar::readFile(file, line),
                    stringToCarType(Car::readFile(file, line)));
        double bp = utils::stod(Car::readFile(file, line));
        double m = utils::stod(Car::readFile(file, line));
        double p = utils::stod(Car::readFile(file, line));
        int d = utils::stoi(Car::readFile(file, line));
        int sc = utils::stoi(Car::readFile(file, line));
        int fc = utils::stoi(Car::readFile(file, line));
        int ec = utils::stoi(Car::readFile(file, line));

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

        Car::readFile(file, line);
        while (line != "" && line.find(",") != std::string::npos) {
          brandNewCar->pushColors(utils::trim(line).substr(0, line.find(",")));
          line = line.substr(line.find(",") + 1);
        }
        if (line != "") brandNewCar->pushColors(line);

        bool errFlag = false;
        while (!file.eof()) {
          CarVariant* cv =
              new CarVariant(Car::readFile(file, line),
                             utils::stod(Car::readFile(file, line)));
          Fuel ft = stringToFuel(Car::readFile(file, line));
          CarTransmission ct = stringToTransmission(Car::readFile(file, line));
          SafetyFeatures sf(utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stoi(Car::readFile(file, line)));

          ComfortFeatures cf(utils::stob(Car::readFile(file, line)),
                             utils::stob(Car::readFile(file, line)),
                             utils::stob(Car::readFile(file, line)),
                             utils::stob(Car::readFile(file, line)),
                             utils::stoi(Car::readFile(file, line)));

          TechnoFeatures tf(utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)));

          double dims[3];
          Car::readFile(file, line);
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

          BuildFeatures bf(Car::readFile(file, line),
                           utils::stod(Car::readFile(file, line)), dims);

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

          Car::readFile(file, line);
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
    std::cerr << "No DataBase directory found in PWD: " << dirPath << std::endl;
  }

  return v;
}

bool NewCar::storeIntoDB(NewCar* brandNewCar) {
  namespace fs = std::filesystem;
  fs::path dirPath = "./db/";
  std::string fname =
      brandNewCar->modelName + "_" + brandNewCar->model + ".txt";
  fs::path filePath = dirPath / fname;

  if (!fs::exists(dirPath)) {
    if (fs::create_directory(dirPath)) {
      // std::cout << "Directory created: " << dirPath << std::endl;
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

SecondHandCar::SecondHandCar(Car& c)
    : Car(c),
      colors("Default"),
      variant(nullptr),
      prevOwner("Default"),
      yearsUsed(INT_MAX) {}

SecondHandCar& SecondHandCar::pushColors(std::string& color) {
  this->colors = color;
  return *this;
}

SecondHandCar& SecondHandCar::pushVariant(CarVariant& variant) {
  this->variant = &variant;
  return *this;
}

SecondHandCar& SecondHandCar::setCarInfo(std::string owner, int yearsUsed,
                                         std::string colors) {
  this->prevOwner = owner;
  this->yearsUsed = yearsUsed;
  this->colors = colors;
  return *this;
}

bool SecondHandCar::isValid() {
  if (utils::trim(colors) == "") return false;
  if (variant == nullptr) return false;
  if (prevOwner == "Default") return false;
  if (yearsUsed == INT_MAX) return false;

  return true;
}

void SecondHandCar::display() {
  std::cout << "Previous Owner: " << this->prevOwner << "\n";
  std::cout << "Years of Service: " << this->yearsUsed << "\n";
  Car::display();
  std::cout << "Color: " << this->colors << "\n";

  variant->display();
  std::cout << "\n";
}

std::vector<SecondHandCar>* SecondHandCar::loadFromDB() {
  namespace fs = std::filesystem;
  std::vector<SecondHandCar>* v = nullptr;

  fs::path dirPath = "./db/preowned";

  if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
    // std::cout << "Directory exists: " << dirPath << std::endl;

    for (const auto& entry : fs::directory_iterator(dirPath)) {
      if (entry.is_regular_file() && entry.path().extension() == ".txt") {
        std::ifstream file(entry.path());
        if (!file) {
          std::cerr << "Could not open file: " << entry.path() << std::endl;
          continue;
        }

        // std::cout << "Reading file: " << entry.path() << std::endl;
        std::string line;

        Car tempCar(Car::readFile(file, line), NewCar::readFile(file, line),
                    stringToCarType(Car::readFile(file, line)));
        double bp = utils::stod(Car::readFile(file, line));
        double m = utils::stod(Car::readFile(file, line));
        double p = utils::stod(Car::readFile(file, line));
        int d = utils::stoi(Car::readFile(file, line));
        int sc = utils::stoi(Car::readFile(file, line));
        int fc = utils::stoi(Car::readFile(file, line));
        int ec = utils::stoi(Car::readFile(file, line));

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

        SecondHandCar* brandNewCar = new SecondHandCar(tempCar);

        brandNewCar->prevOwner = Car::readFile(file, line);
        brandNewCar->yearsUsed = utils::stoi(Car::readFile(file, line));
        brandNewCar->colors = Car::readFile(file, line);

        bool errFlag = false;
        while (!file.eof()) {
          CarVariant* cv =
              new CarVariant(Car::readFile(file, line),
                             utils::stod(Car::readFile(file, line)));
          Fuel ft = stringToFuel(Car::readFile(file, line));
          CarTransmission ct = stringToTransmission(Car::readFile(file, line));
          SafetyFeatures sf(utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stoi(Car::readFile(file, line)));

          ComfortFeatures cf(utils::stob(Car::readFile(file, line)),
                             utils::stob(Car::readFile(file, line)),
                             utils::stob(Car::readFile(file, line)),
                             utils::stob(Car::readFile(file, line)),
                             utils::stoi(Car::readFile(file, line)));

          TechnoFeatures tf(utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)),
                            utils::stob(Car::readFile(file, line)));

          double dims[3];
          Car::readFile(file, line);
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

          BuildFeatures bf(Car::readFile(file, line),
                           utils::stod(Car::readFile(file, line)), dims);

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

          Car::readFile(file, line);
          while (line != "" && line.find(",") != std::string::npos) {
            cv->pushAdditionalFeatures(line.substr(0, line.find(",")));
            line = line.substr(line.find(",") + 1);
          }
          if (line != "") cv->pushAdditionalFeatures(line);

          brandNewCar->pushVariant(*cv);
        }
        if (errFlag) continue;
        if (v == nullptr) {
          v = new std::vector<SecondHandCar>;
        }
        v->push_back(*brandNewCar);
      }
    }
  } else {
    std::cerr << "No DataBase directory found in PWD: " << dirPath << std::endl;
  }

  return v;
}

bool SecondHandCar::storeIntoDB(SecondHandCar* brandNewCar) {
  namespace fs = std::filesystem;
  fs::path dirPath = "./db/preowned";
  std::string fname = brandNewCar->modelName + "_" + brandNewCar->prevOwner +
                      utils::itos(brandNewCar->yearsUsed) + ".txt";
  fs::path filePath = dirPath / fname;

  if (!fs::exists(dirPath)) {
    if (fs::create_directory(dirPath)) {
      // std::cout << "Directory created: " << dirPath << std::endl;
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

  file << brandNewCar->prevOwner << "\n";
  file << brandNewCar->yearsUsed << "\n";
  file << brandNewCar->colors << "\n";

  if (!CarVariant::loadIntoDB(file, *brandNewCar->variant)) {
    return false;
  }

  return true;
}
