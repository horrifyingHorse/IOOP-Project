#include "../include/UI.h"

#include <csignal>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

VariantManager::VariantManager(const char* vn, VariantManager* v)
    : builtVariant(nullptr) {
  feature_index = v ? v->feature_index : 0;
  airBagShow = v ? v->airBagShow : false;
  hasESC = v ? v->hasESC : false;
  hasParkingSensors = v ? v->hasParkingSensors : false;
  hasRearviewCam = v ? v->hasRearviewCam : false;
  hasABS = v ? v->hasABS : false;
  hasAirCondition = v ? v->hasAirCondition : true;
  hasPowerWindows = v ? v->hasPowerWindows : false;
  hasPowerLocks = v ? v->hasPowerLocks : false;
  hasKeylessEntry = v ? v->hasKeylessEntry : false;

  hasBluetoothConn = v ? v->hasBluetoothConn : false;
  hasUSBports = v ? v->hasUSBports : false;
  hasNavigationSys = v ? v->hasNavigationSys : false;
  hasAudioSystem = v ? v->hasAudioSystem : false;

  airConditionNum = v ? v->airConditionNum : "";
  airBagsNum = v ? v->airBagsNum : "";
  bodyMaterial = v ? v->bodyMaterial : "";
  groundClearanceNum = v ? v->groundClearanceNum : "";
  dimL = v ? v->dimL : "";
  dimB = v ? v->dimB : "";
  dimH = v ? v->dimH : "";
  variantName = vn;
  fuelSelect = v ? v->fuelSelect : 0;
  transmissionSelect = v ? v->transmissionSelect : 0;
  if (std::string(vn) == "Variant ") {
    variantName += std::to_string(variantCount);
  }
  variantCount++;

  //    airBagToggle = Toggle(&yesno, &airBagSelect, &airBagShow);
  input_airBagsNum = Input(&airBagsNum, "Number of Airbags");
  input_airBagsNum |= CatchEvent([&](Event event) {
    return event.is_character() && !std::isdigit(event.character()[0]);
  });

  feature_tabs =
      Menu(&feature_entries, &feature_index, MenuOption::HorizontalAnimated());

  safetyFeatTabs = Container::Vertical({
      Checkbox("Airbags", &airBagShow) | size(WIDTH, LESS_THAN, 40),
      input_airBagsNum | size(WIDTH, EQUAL, 40) | Maybe(&airBagShow),
      Checkbox("Anti Lock Braking System", &hasABS) |
          size(WIDTH, LESS_THAN, 40),
      Checkbox("Electronic Stability Control", &hasESC) |
          size(WIDTH, LESS_THAN, 40),
      Checkbox("Read View Camera", &hasRearviewCam) |
          size(WIDTH, LESS_THAN, 40),
      Checkbox("Parking Sensors", &hasParkingSensors) |
          size(WIDTH, LESS_THAN, 40),
  });

  input_airCondition = Input(&airConditionNum, "Air Conditioning");
  input_airCondition |= CatchEvent([&](Event event) {
    return event.is_character() && !std::isdigit(event.character()[0]);
  });

  comfortFeatTabs = Container::Vertical({
      Checkbox("Air Conditioning", &hasAirCondition) |
          size(WIDTH, LESS_THAN, 40),
      input_airCondition | size(WIDTH, EQUAL, 40) | Maybe(&hasAirCondition),
      Checkbox("Power Windows", &hasPowerWindows) | size(WIDTH, LESS_THAN, 40),
      Checkbox("Power Locks", &hasPowerLocks) | size(WIDTH, LESS_THAN, 40),
      Checkbox("Keyless Entry", &hasKeylessEntry) | size(WIDTH, LESS_THAN, 40),
  });

  technicalFeatTabs = Container::Vertical({
      Checkbox("Bluetooth Connection", &hasBluetoothConn) |
          size(WIDTH, LESS_THAN, 40),
      Checkbox("USB Ports", &hasUSBports) | size(WIDTH, LESS_THAN, 40),
      Checkbox("Navigation System", &hasNavigationSys) |
          size(WIDTH, LESS_THAN, 40),
      Checkbox("Audio System", &hasAudioSystem) | size(WIDTH, LESS_THAN, 40),
  });

  input_bodyMaterial = Input(&bodyMaterial, " Body Material ");

  input_groundClearance = Input(&groundClearanceNum, " Ground Clearance ");
  input_groundClearance |= CatchEvent([&](Event event) {
    if (event.is_character()) {
      char ch = event.character()[0];

      if (std::isdigit(ch)) {
        return false;
      } else if (ch == '.') {
        if (groundClearanceNum.find('.') != std::string::npos) {
          return true;
        }
        return false;
      }
      return true;
    }
    return false;
  });

  input_dimensions[0] = Input(&dimL, " Length");
  input_dimensions[0] |= CatchEvent([&](Event event) {
    if (event.is_character()) {
      char ch = event.character()[0];
      if (std::isdigit(ch)) {
        return false;
      } else if (ch == '.') {
        if (dimL.find('.') != std::string::npos) {
          return true;
        }
        return false;
      }
      return true;
    }
    return false;
  });

  input_dimensions[1] = Input(&dimB, " Width");
  input_dimensions[1] |= CatchEvent([&](Event event) {
    if (event.is_character()) {
      char ch = event.character()[0];
      if (std::isdigit(ch)) {
        return false;
      } else if (ch == '.') {
        if (dimB.find('.') != std::string::npos) {
          return true;
        }
        return false;
      }
      return true;
    }
    return false;
  });

  input_dimensions[2] = Input(&dimH, " Height");
  input_dimensions[2] |= CatchEvent([&](Event event) {
    if (event.is_character()) {
      char ch = event.character()[0];
      if (std::isdigit(ch)) {
        return false;
      } else if (ch == '.') {
        if (dimH.find('.') != std::string::npos) {
          return true;
        }
        return false;
      }
      return true;
    }
    return false;
  });

  buildFeatComp = Container::Vertical({
      input_bodyMaterial,
      input_groundClearance | size(WIDTH, EQUAL, 10),
      input_dimensions[0] | size(WIDTH, EQUAL, 10),
      input_dimensions[1] | size(WIDTH, EQUAL, 10),
      input_dimensions[2] | size(WIDTH, EQUAL, 10),
  });

  buildFeatTabs = Renderer(buildFeatComp, [&] {
    return vbox({
        hbox(text("Body Material        : "),
             input_bodyMaterial->Render() | size(WIDTH, EQUAL, 30)),
        hbox(text("Ground Clearance     : "),
             input_groundClearance->Render() | size(WIDTH, EQUAL, 30)),
        hbox(text("Dimensions (in m)    : "),
             input_dimensions[0]->Render() | size(WIDTH, EQUAL, 30)),
        hbox(text("                       "),
             input_dimensions[1]->Render() | size(WIDTH, EQUAL, 30)),
        hbox(text("                       "),
             input_dimensions[2]->Render() | size(WIDTH, EQUAL, 30)),
    });
  });

  input_variantName = Input(&variantName, " Variant Name ");
  input_additionalFeat = Input(&additionalFeat, " Additional Features ");

  dropdown_fueltype = Dropdown(&fueltype, &fuelSelect);
  dropdown_transmission = Dropdown(&transmission, &transmissionSelect);

  input_price = Input(&price, " Price ");
  input_price |= CatchEvent([&](Event event) {
    if (event.is_character()) {
      char ch = event.character()[0];
      if (std::isdigit(ch)) {
        return false;
      } else if (ch == '.') {
        if (price.find('.') != std::string::npos) {
          return true;
        }
        return false;
      }
      return true;
    }
    return false;
  });

  basicInfoComp =
      Container::Vertical({input_variantName, input_price, dropdown_fueltype,
                           dropdown_transmission, input_additionalFeat});

  basicInfo = Renderer(basicInfoComp, [&] {
    return vbox({
        hbox(text("Variant Name           : "),
             input_variantName->Render() | size(WIDTH, EQUAL, 30)),
        hbox(text("Variant Price          : "),
             input_price->Render() | size(WIDTH, EQUAL, 30)),
        hbox(text("Fuel Type              : "),
             dropdown_fueltype->Render() | size(WIDTH, EQUAL, 30)),
        hbox(text("Car Transmission       : "),
             dropdown_transmission->Render() | size(WIDTH, EQUAL, 30)),
        hbox(text("Additional Features    : "),
             input_additionalFeat->Render() | size(WIDTH, EQUAL, 30)),
    });
  });

  tab_content = Container::Tab(
      {safetyFeatTabs, comfortFeatTabs, technicalFeatTabs, buildFeatTabs},
      &feature_index);

  main_container = Container::Vertical({
      basicInfo,
      Container::Horizontal({feature_tabs}),
      tab_content,
  });

  // Create the main vertical container for the variants
  // clang-format off
  renderer = Renderer(main_container, [&] {
    return vbox({
      hbox({basicInfo->Render()}),
      hbox({text(" ")}),
      window(
        text("Features"),
        vbox({
          hbox({
            feature_tabs->Render(),
          }) | hcenter,
          tab_content->Render()
        })
      ) | size(WIDTH, EQUAL, 78) | size(HEIGHT, EQUAL, 15) | hcenter,
    });
  });
  // clang-format off
}

Component VariantManager::getComponent() { return renderer; }

std::string VariantManager::getVarName() { return this->variantName; }

bool VariantManager::build() {
  SafetyFeatures sf(airBagShow, hasABS, hasESC, hasRearviewCam,
                    hasParkingSensors, utils::stoi(airBagsNum));
  ComfortFeatures cf(hasAirCondition, hasPowerWindows, hasPowerLocks,
                     hasKeylessEntry, utils::stoi(airConditionNum));
  TechnoFeatures tf(hasBluetoothConn, hasUSBports, hasNavigationSys,
                    hasAudioSystem);

  double dim[3];
  dim[0] = utils::stod(dimL);
  dim[1] = utils::stod(dimB);
  dim[2] = utils::stod(dimH);
  BuildFeatures bf(bodyMaterial, utils::stod(groundClearanceNum), dim);
  if (!bf.isValid()) return false;

  CarVariant* v = new CarVariant(variantName, utils::stod(price));
  v->setFuelType(fueltypeMap[fuelSelect])
      .setCarTransmission(transmissionMap[transmissionSelect])
      .pushAdditionalFeatures(additionalFeat)
      .setSafetyFeatures(sf)
      .setComfortFeatures(cf)
      .setTechnoFeatures(tf)
      .setBuildFeatures(bf);

  if (!v->isValid()) {
    delete v;
    return false;
  }
  builtVariant = v;
  return true;
}

CarVariant& VariantManager::getVariant() { return *builtVariant; }

VariantManager::~VariantManager() { variantCount--; }

std::vector<std::string> VariantManager::feature_entries = {
    " Safety Features ",
    " Comfort Features ",
    " Technical Features ",
    " Build Features ",
};

std::vector<std::string> VariantManager::yesno = {"Yes", "No"};
int VariantManager::variantCount = 1;
// clang-format off
std::vector<std::string> VariantManager::fueltype = {
  "PETROL", "DIESEL", "CNG", "BIFUEL", "ELECTRIC"
};
// clang-format on
std::vector<Fuel> VariantManager::fueltypeMap = {
    Fuel::PETROL, Fuel::DIESEL, Fuel::CNG, Fuel::BIFUEL, Fuel::ELECTRIC};
std::vector<std::string> VariantManager::transmission = {
    "MANUAL", "SEMIAUTOMATIC", "AUTOMATIC"};
std::vector<CarTransmission> VariantManager::transmissionMap = {
    CarTransmission::MANUAL, CarTransmission::SEMIAUTOMATIC,
    CarTransmission::AUTOMATIC};

RenderVariant::RenderVariant(CarVariant itemV) : itemVariant(itemV) {
  feature_index = 0;
  feature_tabs =
      Menu(&feature_entries, &feature_index, MenuOption::HorizontalAnimated());

  safetyFeatTabs = Container::Vertical({});
  if (itemVariant.safetyFeatures.hasAirbags) {
    safetyFeatTabs->Add(Renderer([&] {
      return text("Airbags : " +
                  utils::itos(itemVariant.safetyFeatures.airbags));
    }));
  }
  if (itemVariant.safetyFeatures.hasABS) {
    safetyFeatTabs->Add(
        Renderer([&] { return text("Anti Lock Braking System"); }));
  }
  if (itemVariant.safetyFeatures.hasESC) {
    safetyFeatTabs->Add(
        Renderer([&] { return text("Electronic Stability Control"); }));
  }
  if (itemVariant.safetyFeatures.hasRearviewCam) {
    safetyFeatTabs->Add(Renderer([&] { return text("Rear View Camera"); }));
  }
  if (itemVariant.safetyFeatures.hasParkingSensors) {
    safetyFeatTabs->Add(Renderer([&] { return text("Parking Sensors"); }));
  }

  comfortFeatTabs = Container::Vertical({});
  if (itemVariant.comfortFeatures.hasAirCondition) {
    comfortFeatTabs->Add(Renderer([&] {
      return text("Air Conditioning : " +
                  utils::itos(itemVariant.comfortFeatures.airCondition));
    }));
  }
  if (itemVariant.comfortFeatures.hasPowerWindows) {
    comfortFeatTabs->Add(Renderer([&] { return text("Power Windows"); }));
  }
  if (itemVariant.comfortFeatures.hasPowerLocks) {
    comfortFeatTabs->Add(Renderer([&] { return text("Power Locks"); }));
  }
  if (itemVariant.comfortFeatures.hasKeylessEntry) {
    comfortFeatTabs->Add(Renderer([&] { return text("Keyless Entry"); }));
  }

  technicalFeatTabs = Container::Vertical({});
  if (itemVariant.technoFeatures.hasBluetoothConn) {
    technicalFeatTabs->Add(
        Renderer([&] { return text("Bluetooth Connection"); }));
  }
  if (itemVariant.technoFeatures.hasUSBports) {
    technicalFeatTabs->Add(Renderer([&] { return text("USB Ports"); }));
  }
  if (itemVariant.technoFeatures.hasNavigationSys) {
    technicalFeatTabs->Add(Renderer([&] { return text("Navigation System"); }));
  }
  if (itemVariant.technoFeatures.hasAudioSystem) {
    technicalFeatTabs->Add(Renderer([&] { return text("Audio System"); }));
  }

  // clang-format off
  buildFeatTabs = Renderer([&] {
    return vbox({
      text("Build Material   : " + itemVariant.buildFeatures.bodyMaterial),
      text("Ground Clearance : " +
           utils::dtos(itemVariant.buildFeatures.groundClearance)),
      text(
        "Dimensions       : " +
         utils::dtos(itemVariant.buildFeatures.dimensions[0]) + " x " +
         utils::dtos(itemVariant.buildFeatures.dimensions[1]) + " x " +
         utils::dtos(itemVariant.buildFeatures.dimensions[2])
      ),
    });
  });
  // clang-format on

  tab_content = Container::Tab(
      {safetyFeatTabs, comfortFeatTabs, technicalFeatTabs, buildFeatTabs},
      &feature_index);

  main_container = Container::Vertical({
      Container::Horizontal({feature_tabs}),
      tab_content,
  });

  // clang-format off
  this->renderer = Renderer(main_container, [&] {
    return vbox({
      text("Variant Name           : " + itemVariant.variantName),
      text("Variant Price          : " + utils::dtos(itemVariant.price)),
      text("Fuel Type              : " + fuelToString(itemVariant.fuelType)),
      text(
        "Car Transmission       : " + transmissionToString(
          itemVariant.carTransmission
        )
      ),
      hbox({text(" ")}),
      window(
        text("Features"),
        vbox({
          hbox({
            feature_tabs->Render(),
          }) | hcenter,
          tab_content->Render()
        })
      ) | size(WIDTH, EQUAL, 78) | size(HEIGHT, EQUAL, 15) | hcenter,
    });
  });
  // clang-format on
}

Component RenderVariant::getComponent() { return this->renderer; }

std::vector<std::string> RenderVariant::feature_entries = {
    " Safety Features ",
    " Comfort Features ",
    " Technical Features ",
    " Build Features ",
};

SearchResultRender::SearchResultRender(NewCar car)
    : itemNew(car), itemOld(car) {
  this->colorIndex = 0;

  this->colorDropDown =
      Dropdown(&itemNew.colors, &colorIndex) | size(WIDTH, EQUAL, 20);

  moreInfo = Button(
      " Know More ", [&] { SearchResultRender::renderInformation(itemNew); },
      ButtonOption::Ascii());

  buyButton = Button(" Buy ", [&] { buyCar(itemNew); }, ButtonOption::Ascii());

  interactiveContainer = Container::Vertical(
      {colorDropDown, Container::Horizontal({moreInfo, buyButton})});

  // clang-format off
  this->basicInfo = Renderer(interactiveContainer, [&] {
    return vbox({
      text("Model                 : " + itemNew.model),
      hbox({
        text("Colors                : "),
        colorDropDown->Render()
      }),
      text("Car Type              : " + carTypeToString(itemNew.carType)),
      text("Base Price            : " + utils::dtos((itemNew.basePrice))),
      separator(),
      text("Mileage               : " + utils::dtos((itemNew.mileage))),
      text("Power                 : " + utils::dtos((itemNew.power))),
      separator(),
      text("Fuel Tank Capacity    : " + utils::dtos((itemNew.fuelTankCapacity))),
      text("Seating Capacity      : " + utils::dtos((itemNew.seatingCapacity))),
      text("Number of Doors       : " + utils::dtos((itemNew.numOfDoors))),
      text("Engine Capacity (cc)  : " + utils::dtos((itemNew.engineCapacity))),
      hbox({
          moreInfo->Render(),
          buyButton->Render(),
      }) | hcenter,
    }) | border | xflex_grow | hcenter;
  });

  collapsible = Collapsible(
    " " + itemNew.modelName + " ",
    Inner({ this->basicInfo, })
  );

  this->renderer = Renderer(Container::Vertical({collapsible}), [&] {
    return vbox({collapsible->Render()});
  });
  // clang-format on
}

SearchResultRender::SearchResultRender(SecondHandCar car)
    : itemOld(car), itemNew(car) {
  this->colorIndex = 0;

  moreInfo = Button(
      " Know More ", [&] { SearchResultRender::renderInformation(itemOld); },
      ButtonOption::Ascii());

  buyButton = Button(" Buy ", [&] { buyCar(itemOld); }, ButtonOption::Ascii());

  interactiveContainer =
      Container::Vertical({Container::Horizontal({moreInfo, buyButton})});

  // clang-format off
  this->basicInfo = Renderer(interactiveContainer, [&] {
    return vbox({
      text("Model                 : " + itemOld.model),
      hbox({
        text("Color                 : " + itemOld.colors)
      }),
      text("Car Type              : " + carTypeToString(itemOld.carType)),
      text("Base Price            : " + utils::dtos((itemOld.basePrice))),
      separator(),
      text("Mileage               : " + utils::dtos((itemOld.mileage))),
      text("Power                 : " + utils::dtos((itemOld.power))),
      separator(),
      text("Fuel Tank Capacity    : " + utils::dtos((itemOld.fuelTankCapacity))),
      text("Seating Capacity      : " + utils::dtos((itemOld.seatingCapacity))),
      text("Number of Doors       : " + utils::dtos((itemOld.numOfDoors))),
      text("Engine Capacity (cc)  : " + utils::dtos((itemOld.engineCapacity))),
      hbox({
        moreInfo->Render(),
        buyButton->Render()
      }) | hcenter,
    }) | border | xflex_grow | hcenter;
  });

  collapsible = Collapsible(
    " " + itemOld.modelName + " ",
    Inner({ this->basicInfo,
    })
  );

  this->renderer = Renderer(Container::Vertical({collapsible}), [&] {
    return vbox({collapsible->Render()});
  });
  // clang-format on
}

Component& SearchResultRender::getComponent() { return renderer; }

Component SearchResultRender::Inner(std::vector<Component> children) {
  Component vlist = Container::Vertical(std::move(children));
  return Renderer(vlist, [vlist] {
    return hbox({
        text(" "),
        vlist->Render(),
    });
  });
}

Component SearchResultRender::Empty() {
  return std::make_shared<ComponentBase>();
}

void SearchResultRender::renderInformation(NewCar& item) {
  auto screen = ScreenInteractive::Fullscreen();
  auto style = ButtonOption::Animated(Color::Default, Color::GrayDark,
                                      Color::Default, Color::White);

  int colorIndex = 0;
  auto colorDropDown =
      Dropdown(&item.colors, &colorIndex) | size(WIDTH, EQUAL, 20);

  // clang-format off
  auto basicInfoTab = Renderer(colorDropDown, [&] {
    return vbox({
      window(
        text("New Car Info"),
        vbox({
          hbox(text("Model Name                 : " + item.model)),
          hbox(text("Model                      : " + item.modelName)),
          hbox(
            text("Colors                     : "),
            colorDropDown->Render()
          ),
          hbox(text("Car Type                   : " + carTypeToString(item.carType))),
          hbox(text("Base Price                 : " + utils::dtos(item.basePrice))),
          separator(),
          hbox(text("Mileage                    : " + utils::dtos(item.mileage))),
          hbox(text("Power (bhp)                : " + utils::dtos(item.power))),
          separator(),
          hbox(text("Fuel Tank Capacity (liters): " + utils::dtos(item.fuelTankCapacity))),
          hbox(text("Seating Capacity           : " + utils::dtos(item.seatingCapacity))),
          hbox(text("Number of Doors            : " + utils::dtos(item.numOfDoors))),
          hbox(text("Engine Capacity (cc)       : " + utils::dtos(item.engineCapacity))),
        })
      )
    });
  });
  // clang-format on

  auto quitBut = Button(" x ", [&] { screen.Exit(); }, style);
  auto buyButton = Button(" Buy ", [&] { buyCar(item); }, style);

  int tab_index = 0;
  std::vector<std::string> tab_entries = {" Basic Details "};
  std::vector<Component> tabs = {basicInfoTab};
  std::vector<RenderVariant> vars = {};

  for (auto var : item.variants) {
    tab_entries.push_back(" " + var.variantName + " ");
    RenderVariant* newVariant = new RenderVariant(var);
    vars.push_back(*newVariant);
    tabs.push_back(newVariant->getComponent());
  }

  auto tab_selection =
      Menu(&tab_entries, &tab_index, MenuOption::HorizontalAnimated());
  auto tab_content = Container::Tab(tabs, &tab_index);

  auto main_container = Container::Vertical({
      Container::Horizontal({tab_selection, buyButton, quitBut}),
      tab_content,
  });

  auto main_renderer = Renderer(main_container, [&] {
    return vbox({
        text(item.modelName + " Details") | bold | hcenter,
        hbox({tab_selection->Render() | flex, buyButton->Render(),
              quitBut->Render()}),
        tab_content->Render() | flex,
    });
  });

  screen.Loop(main_renderer);
}

void SearchResultRender::renderInformation(SecondHandCar& item) {
  auto screen = ScreenInteractive::Fullscreen();
  auto style = ButtonOption::Animated(Color::Default, Color::GrayDark,
                                      Color::Default, Color::White);

  // clang-format off
  auto basicInfoTab = Renderer([&] {
    return vbox({
      window(
        text("New Car Info"),
        vbox({
          hbox(text("Model Name                 : " + item.model)),
          hbox(text("Model                      : " + item.modelName)),
          hbox(text("Colors                     : " + item.colors)),
          hbox(text("Car Type                   : " +
                    carTypeToString(item.carType))),
          hbox(text("Base Price                 : " +
                    utils::dtos(item.basePrice))),
          separator(),
          hbox(text("Mileage                    : " +
                    utils::dtos(item.mileage))),
          hbox(text("Power (bhp)                : " +
                    utils::dtos(item.power))),
          separator(),
          hbox(text("Fuel Tank Capacity (liters): " +
                    utils::dtos(item.fuelTankCapacity))),
          hbox(text("Seating Capacity           : " +
                    utils::dtos(item.seatingCapacity))),
          hbox(text("Number of Doors            : " +
                    utils::dtos(item.numOfDoors))),
          hbox(text("Engine Capacity (cc)       : " +
                    utils::dtos(item.engineCapacity)))
         })
      ),
      hbox({text(" ")}),
      window(
        text("Details"),
        vbox({
          hbox(text("Previous Owner             : " + item.prevOwner)),
          hbox(text("Years of Service           : " +
                    utils::itos(item.yearsUsed) + " yr")),
        })
      ),
    });
  });
  // clang-format on

  auto quitBut = Button(" x ", [&] { screen.Exit(); }, style);
  int tab_index = 0;
  std::vector<std::string> tab_entries = {" Basic Details "};
  std::vector<Component> tabs = {basicInfoTab};
  std::vector<RenderVariant> vars = {};
  tab_entries.push_back(" " + item.variant->variantName + " ");

  RenderVariant* newVariant = new RenderVariant(*item.variant);
  vars.push_back(*newVariant);
  tabs.push_back(newVariant->getComponent());

  auto tab_selection =
      Menu(&tab_entries, &tab_index, MenuOption::HorizontalAnimated());
  auto tab_content = Container::Tab(tabs, &tab_index);

  auto main_container = Container::Vertical({
      Container::Horizontal({tab_selection, quitBut}),
      tab_content,
  });

  auto main_renderer = Renderer(main_container, [&] {
    return vbox({
        text(item.modelName + " Details") | bold | hcenter,
        hbox({tab_selection->Render() | flex, quitBut->Render()}),
        tab_content->Render() | flex,
    });
  });

  screen.Loop(main_renderer);
}

CarSearchEngine::CarSearchEngine(std::vector<NewCar> inventoryNewCar,
                                 std::vector<SecondHandCar> inventorySHCar,
                                 Component* renderer)
    : inventoryNewCar(inventoryNewCar),
      inventorySHCar(inventorySHCar),
      mode(0),
      renderer(renderer),
      resultNewVector({}),
      resultSHVector({}),
      modelNameStr(""),
      modelNameLen(0) {}

Component* CarSearchEngine::render() {
  (*renderer)->DetachAllChildren();

  switch (this->mode) {
    case 0: {
      for (auto car : resultNewVector) {
        SearchResultRender* r = new SearchResultRender(car);
        (*renderer)->Add(r->getComponent());
      }
      break;
    }

    case 1: {
      for (auto car : resultSHVector) {
        SearchResultRender* r = new SearchResultRender(car);
        (*renderer)->Add(r->getComponent());
      }
      break;
    }
  }

  return this->renderer;
}

CarSearchEngine& CarSearchEngine::modelName(std::string s) {
  utils::trim(s);
  utils::toLowerCase(s);

  switch (this->mode) {
    case 0: {
      if (s.length() <= this->modelNameLen) resultNewVector.clear();
      if (!resultNewVector.empty()) {
        for (auto it = resultNewVector.begin(); it != resultNewVector.end();) {
          std::string cmpStr = it->modelName;
          std::string cmpStr2 = it->model;
          if (utils::toLowerCase(cmpStr).find(s) == std::string::npos &&
              utils::toLowerCase(cmpStr2).find(s) == std::string::npos)
            it = resultNewVector.erase(it);
          else
            ++it;
        }
      } else {
        for (auto car : inventoryNewCar) {
          std::string cmpStr = car.modelName;
          std::string cmpStr2 = car.model;
          if (utils::toLowerCase(cmpStr).find(s) != std::string::npos ||
              utils::toLowerCase(cmpStr2).find(s) != std::string::npos) {
            resultNewVector.push_back(car);
          }
        }
      }
      break;
    }

    case 1:
      if (s.length() <= this->modelNameLen) resultSHVector.clear();
      if (!resultSHVector.empty()) {
        for (auto it = resultSHVector.begin(); it != resultSHVector.end();) {
          std::string cmpStr = it->modelName;
          std::string cmpStr2 = it->model;
          if (utils::toLowerCase(cmpStr).find(s) == std::string::npos &&
              utils::toLowerCase(cmpStr2).find(s) == std::string::npos)
            it = resultSHVector.erase(it);
          else
            ++it;
        }
      } else {
        for (auto car : inventorySHCar) {
          std::string cmpStr = car.modelName;
          std::string cmpStr2 = car.model;
          if (utils::toLowerCase(cmpStr).find(s) != std::string::npos ||
              utils::toLowerCase(cmpStr2).find(s) != std::string::npos) {
            resultSHVector.push_back(car);
          }
        }
      }
      break;
  }

  this->modelNameLen = s.length();
  this->modelNameStr = s;

  return *this;
}

CarSearchEngine& CarSearchEngine::setMode(int mode) {
  resultNewVector.clear();
  resultSHVector.clear();

  this->mode = mode;
  this->modelName(this->modelNameStr);
  this->render();
  return *this;
}

void managerSalesView(Manager& m) {
  auto screen = ScreenInteractive::Fullscreen();

  namespace fs = std::filesystem;

  std::vector<Customer*> brandNewSales;
  std::vector<Customer*> preownedSales;

  double revenue[2] = {0, 0};
  int count[2] = {0, 0};

  fs::path dirPath = "./db/reciept/";
  if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
    for (const auto& entry : fs::directory_iterator(dirPath)) {
      if (entry.is_regular_file() && entry.path().extension() == ".txt") {
        std::ifstream file(entry.path());
        if (!file) {
          std::cerr << "Could not open file: " << entry.path() << std::endl;
          continue;
        }

        std::string line;
        Customer* c = new Customer();
        getline(file, line);
        c->billNum = utils::stoi(line);
        getline(file, line);
        c->date = line;
        getline(file, line);
        c->name = line;
        getline(file, line);
        c->address = line;
        getline(file, line);
        c->phoneNumber = line;
        getline(file, line);
        c->email = line;
        getline(file, line);
        c->carModel = line;
        getline(file, line);
        c->color = line;
        getline(file, line);
        c->carVariant = line;
        getline(file, line);
        c->price = utils::stod(line);
        if (!Customer::isValid(*c)) {
          delete c;
          continue;
        }

        brandNewSales.push_back(c);
        revenue[0] += c->price;
        count[0]++;
      }
    }
  }

  dirPath = "./db/reciept/preowned/";
  if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
    for (const auto& entry : fs::directory_iterator(dirPath)) {
      if (entry.is_regular_file() && entry.path().extension() == ".txt") {
        std::ifstream file(entry.path());
        if (!file) {
          std::cerr << "Could not open file: " << entry.path() << std::endl;
          continue;
        }

        std::string line;
        Customer* c = new Customer();
        getline(file, line);
        c->setPreOwned(line);
        getline(file, line);
        c->billNum = utils::stoi(line);
        getline(file, line);
        c->date = line;
        getline(file, line);
        c->name = line;
        getline(file, line);
        c->address = line;
        getline(file, line);
        c->phoneNumber = line;
        getline(file, line);
        c->email = line;
        getline(file, line);
        c->carModel = line;
        getline(file, line);
        c->color = line;
        getline(file, line);
        c->carVariant = line;
        getline(file, line);
        c->price = utils::stod(line);
        if (!Customer::isValid(*c)) {
          delete c;
          continue;
        }

        preownedSales.push_back(c);
        revenue[1] += c->price;
        count[1]++;
      }
    }
  }

  std::vector<std::string> new_entries = {};
  for (auto cust : brandNewSales) {
    new_entries.push_back(utils::itos(cust->billNum) + "   " + cust->date +
                          "   " + cust->carModel);
  }
  int new_selected = 0;
  MenuOption new_option;
  new_option.on_enter = [&] {
    managerSalesViewExpand(*brandNewSales[new_selected]);
  };
  auto new_menu = Menu(&new_entries, &new_selected, new_option);

  std::vector<std::string> old_entries = {};
  for (auto cust : preownedSales) {
    old_entries.push_back(utils::itos(cust->billNum) + "   " + cust->date +
                          "   " + cust->carModel);
  }
  int old_selected = 0;
  MenuOption old_option;
  old_option.on_enter = [&] {
    managerSalesViewExpand(*preownedSales[old_selected]);
  };
  auto old_menu = Menu(&old_entries, &old_selected, old_option);

  std::vector<std::string> tab_entries{
      " Brand New Cars ",
      " Others ",
  };
  int tab_index = 0;
  auto tab_selection =
      Menu(&tab_entries, &tab_index, MenuOption::HorizontalAnimated());
  auto tab_content = Container::Tab({new_menu, old_menu}, &tab_index);

  auto quitBut = Button(" x ", [&] { screen.Exit(); }, ButtonOption::Ascii());

  Component main_container =
      Container::Vertical({quitBut, tab_selection, tab_content});

  // clang-format off
  Component main_renderer = Renderer(main_container, [&] {
    const int width = 50;
    return vbox({
      vbox({
        hbox({
          text(" Sales Stats: ") | flex,
          quitBut->Render()
        }) | size(WIDTH, EQUAL, width),
        vbox({
          tab_selection->Render(),
          tab_content->Render() | vscroll_indicator
        }) | vscroll_indicator | border
           | size(WIDTH, EQUAL, width) | size(HEIGHT, EQUAL, 20),
        vbox({
          text("Total Revenue: " + utils::dtos(revenue[tab_index])),
          text("Total Cars Sold: " + utils::itos(count[tab_index])),
          separatorEmpty(),
          text("Grand Total:"),
          text(utils::itos(count[0] + count[1]) + " Cars sold worth Rs. " + utils::dtos(revenue[0] + revenue[1]))
        }) | size(WIDTH, EQUAL, width),
      }) | flex | center
    }) | yflex | center;
  });
  // clang-format on

  screen.Loop(main_renderer);
}

void managerSalesViewExpand(Customer& c) {
  auto screen = ScreenInteractive::Fullscreen();
  auto quitBut = Button(" x ", [&] { screen.Exit(); }, ButtonOption::Ascii());
  Component main_container = Container::Vertical({quitBut});

  // clang-format off
  Component main_renderer = Renderer(main_container, [&] {
    return vbox({
      window(
        text("Sale Information"),
        vbox({
          hbox({
            text(c.date) | flex,
            quitBut->Render(),
          }),
          text("Bill no. " + utils::itos(c.billNum)),
          separatorLight(),
          hbox({
            text("Name      : " + c.name),
          }),
          hbox({
            text("Address   : " + c.address),
          }),
          hbox({
            text("Email     : " + c.email),
          }),
          hbox({
            text("Phone No. : " + c.phoneNumber),
          }) | size(WIDTH, EQUAL, 40),
          separatorEmpty(),
          hbox({
            text("Car Model : " + c.carModel),
          }),
          hbox({
            text("Color     : " + utils::trim(c.color)),
          }),
          hbox({
            text("Variant   : " + c.carVariant),
          }),
          hbox({
            text("Cost      : " + utils::dtos(c.price)),
          }),
        })
      ) | center | flex
    }) | flex;
  });
  // clang-format on

  screen.Loop(main_renderer);
}
