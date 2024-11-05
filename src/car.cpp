#include "../include/Car.h"

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
