#ifndef UI_H
#define UI_H

#include "Car.h"
#include "Humans.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "utils.h"

int profileSelect();

bool managerLogin(Manager& m);

void managerProfile(std::vector<NewCar>& inventoryNewCar,
                    std::vector<SecondHandCar>& inventorySHCar);
int mainMenuManager();

void employeeProfile(std::vector<NewCar>& inventoryNewCar,
                     std::vector<SecondHandCar>& inventorySHCar);
int mainMenuEmployee();

void customerProfile(std::vector<NewCar>& inventoryNewCar,
                     std::vector<SecondHandCar>& inventorySHCar);
int mainMenuCustomer();

void addEmployee(Manager& m);
void removeEmployee(Manager& m);

void buyCar(NewCar& c);
void buyCar(SecondHandCar& c);

NewCar* regCar();

SecondHandCar* regSecondHandCar();

int searchCars(std::vector<NewCar>& inventoryNewCar,
               std::vector<SecondHandCar>& inventorySHCar);

using namespace ftxui;
class VariantManager {
 public:
  VariantManager(const char* vn = "Variant ", VariantManager* v = nullptr);
  ~VariantManager();

  Component getComponent();
  std::string getVarName();
  bool build();
  CarVariant& getVariant();

 private:
  CarVariant* builtVariant;

  bool airBagShow;
  bool hasABS;
  bool hasESC;
  bool hasRearviewCam;
  bool hasParkingSensors;

  bool hasAirCondition;
  bool hasPowerWindows;
  bool hasPowerLocks;
  bool hasKeylessEntry;

  bool hasBluetoothConn;
  bool hasUSBports;
  bool hasNavigationSys;
  bool hasAudioSystem;

  std::string airConditionNum;

  static std::vector<std::string> feature_entries;

  static std::vector<std::string> yesno;
  static int variantCount;
  static std::vector<std::string> fueltype;
  static std::vector<Fuel> fueltypeMap;
  static std::vector<std::string> transmission;
  static std::vector<CarTransmission> transmissionMap;

  int feature_index;
  int airBagSelect;
  int fuelSelect;
  int transmissionSelect;

  std::string variantName;
  std::string additionalFeat;
  std::string airBagsNum;
  std::string bodyMaterial;
  std::string groundClearanceNum;
  std::string dimL, dimB, dimH;
  std::string price;

  Component basicInfo, basicInfoComp;
  Component input_variantName;
  Component input_additionalFeat;
  Component input_price;
  Component dropdown_fueltype;
  Component dropdown_transmission;

  Component input_airBagsNum;
  Component hinput_asABS;
  Component input_hasESC;
  Component input_hasRearviewCam;
  Component input_hasParkingSensors;

  Component input_airCondition;

  Component input_bodyMaterial;
  Component input_groundClearance;
  Component input_dimensions[3];  // lxbxh

  Component safetyFeatTabs;
  Component comfortFeatTabs;
  Component technicalFeatTabs;
  Component buildFeatComp, buildFeatTabs;

  Component feature_tabs;
  Component tab_content;
  Component main_container;
  Component airBagToggle;
  Component renderer;  // Renderer for the variant manager
};

#endif  // !UI_H
