#include <cstdio>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <string>
#include <vector>

#include "../include/Car.h"
#include "../include/UI.h"
#include "../include/utils.h"

class RenderVariant {
 public:
  RenderVariant(CarVariant itemV) : itemVariant(itemV) {
    feature_index = 0;
    feature_tabs = Menu(&feature_entries, &feature_index,
                        MenuOption::HorizontalAnimated());

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
      technicalFeatTabs->Add(
          Renderer([&] { return text("Navigation System"); }));
    }
    if (itemVariant.technoFeatures.hasAudioSystem) {
      technicalFeatTabs->Add(Renderer([&] { return text("Audio System"); }));
    }

    buildFeatTabs = Renderer([&] {
      return vbox({
          text("Build Material   : " + itemVariant.buildFeatures.bodyMaterial),
          text("Ground Clearance : " +
               utils::dtos(itemVariant.buildFeatures.groundClearance)),
          text("Dimensions       : " +
               utils::dtos(itemVariant.buildFeatures.dimensions[0]) + " x " +
               utils::dtos(itemVariant.buildFeatures.dimensions[1]) + " x " +
               utils::dtos(itemVariant.buildFeatures.dimensions[2])),
      });
    });

    tab_content = Container::Tab(
        {safetyFeatTabs, comfortFeatTabs, technicalFeatTabs, buildFeatTabs},
        &feature_index);

    main_container = Container::Vertical({
        Container::Horizontal({feature_tabs}),
        tab_content,
    });

    this->renderer = Renderer(main_container, [&] {
      return vbox({
          text("Variant Name           : " + itemVariant.variantName),
          text("Variant Price          : " + utils::dtos(itemVariant.price)),
          text("Fuel Type              : " +
               fuelToString(itemVariant.fuelType)),
          text("Car Transmission       : " +
               transmissionToString(itemVariant.carTransmission)),
          hbox({text(" ")}),
          window(text("Features"), vbox({hbox({
                                             feature_tabs->Render(),
                                         }) | hcenter,
                                         tab_content->Render()})) |
              size(WIDTH, EQUAL, 78) | size(HEIGHT, EQUAL, 15) | hcenter,
      });
    });
  }

  Component getComponent() { return this->renderer; }

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

  static inline std::vector<std::string> feature_entries = {
      " Safety Features ",
      " Comfort Features ",
      " Technical Features ",
      " Build Features ",
  };
};

class SearchResultRender {
 public:
  SearchResultRender(NewCar& car) : item(car) {
    this->colorIndex = 0;

    this->colorDropDown =
        Dropdown(&item.colors, &colorIndex) | size(WIDTH, EQUAL, 20);

    moreInfo = Button(
        "Know More ", [&] { SearchResultRender::renderInformation(item); },
        ButtonOption::Ascii());

    interactiveContainer = Container::Vertical({colorDropDown, moreInfo});

    this->basicInfo = Renderer(interactiveContainer, [&] {
      return vbox({
                 text("Model                 : " + item.model),
                 hbox({text("Colors                : "),
                       colorDropDown->Render()}),
                 text("Car Type              : " +
                      carTypeToString(item.carType)),
                 text("Base Price            : " +
                      utils::dtos((item.basePrice))),
                 separator(),
                 text("Mileage               : " +
                      utils::dtos((item.mileage))),
                 text("Power                 : " +
                      utils::dtos((item.power))),
                 separator(),
                 text("Fuel Tank Capacity    : " +
                      utils::dtos((item.fuelTankCapacity))),
                 text("Seating Capacity      : " +
                      utils::dtos((item.seatingCapacity))),
                 text("Number of Doors       : " +
                      utils::dtos((item.numOfDoors))),
                 text("Engine Capacity (cc)  : " +
                      utils::dtos((item.engineCapacity))),
                 moreInfo->Render() | hcenter,
             }) |
             border | xflex_grow | hcenter;
    });

    collapsible = Collapsible(" " + item.modelName + " ",
                              Inner({
                                  this->basicInfo,
                              }));  // | size(WIDTH, LESS_THAN, 20);

    this->renderer = Renderer(Container::Vertical({collapsible}), [&] {
      return vbox({collapsible->Render()});
      // return hbox({collapsible->Render(), text(" " + item.model) | dim});
    });
  }

  Component& getComponent() { return renderer; }

 protected:
  int colorIndex;

  NewCar item;
  Component renderer;

  Component interactiveContainer;

  Component basicInfo;
  Component colorDropDown;
  Component collapsible;

  Component moreInfo;

  Component Inner(std::vector<Component> children) {
    Component vlist = Container::Vertical(std::move(children));
    return Renderer(vlist, [vlist] {
      return hbox({
          text(" "),
          vlist->Render(),
      });
    });
  }

  Component Empty() { return std::make_shared<ComponentBase>(); }

  void renderInformation(NewCar& item) {
    auto screen = ScreenInteractive::Fullscreen();
    auto style = ButtonOption::Animated(Color::Default, Color::GrayDark,
                                        Color::Default, Color::White);

    int colorIndex = 0;
    auto colorDropDown =
        Dropdown(&item.colors, &colorIndex) | size(WIDTH, EQUAL, 20);

    auto basicInfoTab = Renderer(colorDropDown, [&] {
      return vbox({window(
          text("New Car Info"),
          vbox({
              hbox(text("Model Name                 : " + item.model)),
              hbox(text("Model                      : " + item.modelName)),
              hbox(text("Colors                     : "),
                   colorDropDown->Render()),
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
                        utils::dtos(item.engineCapacity))),
          }))});
    });

    auto quitBut = Button(" x ", [&] { screen.Exit(); }, style);

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
};

class CarSearchEngine {
 public:
  CarSearchEngine(std::vector<NewCar> inventoryNewCar, Component* renderer)
      : inventoryNewCar(inventoryNewCar),
        renderer(renderer),
        resultVector({}),
        modelNameLen(0) {}

  Component* render() {
    (*renderer)->DetachAllChildren();

    for (auto car : resultVector) {
      SearchResultRender* r = new SearchResultRender(car);
      (*renderer)->Add(r->getComponent());
    }

    return this->renderer;
  }

  CarSearchEngine& modelName(std::string s) {
    utils::trim(s);
    utils::toLowerCase(s);

    if (s.length() <= this->modelNameLen) resultVector.clear();

    if (!resultVector.empty()) {
      for (auto it = resultVector.begin(); it != resultVector.end();) {
        std::string cmpStr = it->modelName;
        std::string cmpStr2 = it->model;
        if (utils::toLowerCase(cmpStr).find(s) == std::string::npos &&
            utils::toLowerCase(cmpStr2).find(s) == std::string::npos)
          it = resultVector.erase(it);
        else
          ++it;
      }
    } else {
      for (auto car : inventoryNewCar) {
        std::string cmpStr = car.modelName;
        std::string cmpStr2 = car.model;
        if (utils::toLowerCase(cmpStr).find(s) != std::string::npos ||
            utils::toLowerCase(cmpStr2).find(s) != std::string::npos) {
          resultVector.push_back(car);
        }
      }
    }

    this->modelNameLen = s.length();

    return *this;
  }

 protected:
  std::vector<NewCar> inventoryNewCar;
  std::vector<NewCar> resultVector;

  Component* renderer;

  int modelNameLen;
};

int searchCars(std::vector<NewCar>& inventoryNewCar) {
  auto screen = ScreenInteractive::Fullscreen();

  auto searchResults = Container::Vertical({});

  CarSearchEngine engine(inventoryNewCar, &searchResults);

  /* Implement Search for:
   * [√] Model Name
   * [×] Model
   * [ ] Car Type
   * [ ] Fuel Type
   * [ ] Transmission
   *
   * [×] Seating Capacit?
   */

  std::string modelName;

  auto style = ButtonOption::Animated(Color::Default, Color::GrayDark,
                                      Color::Default, Color::White);
  auto quitBut = Button(" x ", [&] { screen.Exit(); }, style);

  Component input_model_name =
      Input(&modelName, "Model Name or Model", InputOption{.on_change = [&]() {
        engine.modelName(modelName);
        engine.render();
      }});

  // input_model_name |= CatchEvent([&](Event event) {
  //   if (event.is_character()) {
  //     engine.modelName(modelName + event.character());
  //     engine.render();
  //   }
  //   return false;
  // });

  auto searchParams = Container::Horizontal({
      input_model_name,

  });

  auto mainContainer = Container::Vertical({
      quitBut,
      searchParams,
      searchResults,

  });

  auto mainRenderer = Renderer(mainContainer, [&] {
    return vbox({
               separatorDashed(),
               hbox({
                   text("Search Car per Your Needs!") | bold | hcenter | flex,
                   quitBut->Render(),
               }),
               separatorDashed(),
               hbox({text("")}),

               vbox({
                   hbox({
                       text("Model Name: "),
                       input_model_name->Render() | size(WIDTH, EQUAL, 20) |
                           flex,
                   }),
               }),

               searchResults->Render() | vscroll_indicator | frame | flex,
           }) |
           border;
  });

  screen.Loop(mainRenderer);

  return 0;
}
