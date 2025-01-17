#ifndef UI_H
#define UI_H

#include <memory>

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
void managerSalesView(Manager& m);
void managerSalesViewExpand(Customer& c);

int mainMenuEmployee();
void employeeProfile(std::vector<NewCar>& inventoryNewCar,
                     std::vector<SecondHandCar>& inventorySHCar);

int mainMenuCustomer();
void customerProfile(std::vector<NewCar>& inventoryNewCar,
                     std::vector<SecondHandCar>& inventorySHCar);

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
  std::shared_ptr<CarVariant> builtVariant;

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
  Component renderer;
};

class RenderVariant {
 public:
  RenderVariant(CarVariant itemV);
  Component getComponent();

 protected:
  int feature_index;

  CarVariant itemVariant;

  Component feature_tabs;
  Component safetyFeatTabs;
  Component comfortFeatTabs;
  Component technicalFeatTabs;
  Component buildFeatTabs;

  Component tab_content;
  Component main_container;

  Component renderer;

  static std::vector<std::string> feature_entries;
};

class SearchResultRender {
 public:
  SearchResultRender(NewCar car);
  SearchResultRender(SecondHandCar car);
  Component& getComponent();

 protected:
  int colorIndex;

  NewCar itemNew;
  SecondHandCar itemOld;
  Component renderer;

  Component interactiveContainer;

  Component basicInfo;
  Component colorDropDown;
  Component collapsible;

  Component moreInfo;
  Component buyButton;

  Component Inner(std::vector<Component> children);

  Component Empty();

  void renderInformation(NewCar& item);

  void renderInformation(SecondHandCar& item);
};

class CarSearchEngine {
 public:
  CarSearchEngine(std::vector<NewCar> inventoryNewCar,
                  std::vector<SecondHandCar> inventorySHCar,
                  Component* renderer);
  ~CarSearchEngine();

  Component* render();

  CarSearchEngine& modelName(std::string s);
  CarSearchEngine& setMode(int mode);

 protected:
  std::vector<NewCar> inventoryNewCar;
  std::vector<SecondHandCar> inventorySHCar;

  std::vector<NewCar> resultNewVector;
  std::vector<SecondHandCar> resultSHVector;

  std::string modelNameStr;

  std::vector<SearchResultRender*> searchResults;
  Component* renderer;

  int modelNameLen;
  int mode;

 private:
  void clearSearchResults();
};

#endif  // !UI_H
