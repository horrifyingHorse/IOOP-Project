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
