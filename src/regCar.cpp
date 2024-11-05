#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>   // for filler, text, hbox, vbox
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include <string>
#include <vector>

#include "../include/Car.h"
#include "../include/UI.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/node.hpp"      // for Render
#include "ftxui/screen/color.hpp"  // for ftxui

int stoi(std::string& s) { return (s == "") ? 0 : std::stoi(s); }

int stod(std::string& s) { return (s == "") ? 0 : std::stod(s); }

using namespace ftxui;
NewCar* regCar() {
  NewCar* brandNewCar = nullptr;
  std::vector<VariantManager*> v;
  auto screen = ScreenInteractive::Fullscreen();

  int tab_index = 0;
  std::vector<std::string> tab_entries = {
      " Basic Details ",
      " Base Variant ",
  };

  std::string modelName, model, colors = "";
  std::string basePriceStr, mileageStr, powerStr;  // Use strings for input
  double basePrice, mileage, power;
  std::string fuelTankCapacity, seatingCapacity, numOfDoors, engineCapacity;
  std::vector<std::string> cartype = {
      "COMPACTSUV", "CONVERTIBLE", "DEFAULT", "HATCHBACK", "JEEP",
      "LIMOUSINE",  "LUXURYCAR",   "SEDAN",   "SPORTS",    "SUV",
  };
  std::vector<CarType> ct = {
      CarType::COMPACTSUV, CarType::CONVERTIBLE, CarType::DEFAULT,
      CarType::HATCHBACK,  CarType::JEEP,        CarType::LIMOUSINE,
      CarType::LUXURYCAR,  CarType::SEDAN,       CarType::SPORTS,
      CarType::SUV,
  };

  int cartypeIndex = 2;

  Component input_model_name = Input(&modelName, "Model Name");
  Component input_model = Input(&model, "Model");
  Component input_colors = Input(&colors, "Available Colors (, separated)");

  Component input_base_price = Input(&basePriceStr, "Base Price");
  input_base_price |= CatchEvent([&](Event event) {
    if (event.is_character()) {
      char ch = event.character()[0];

      // Allow digits and a single decimal point
      if (std::isdigit(ch)) {
        return false;  // Allow digits
      } else if (ch == '.') {
        if (basePriceStr.find('.') != std::string::npos) {
          return true;
        }
        return false;  // Allow the decimal point
      }
      return true;  // Ignore other characters
    }
    return false;  // Ignore other event types
  });

  Component input_mileage = Input(&mileageStr, "Mileage");
  input_mileage |= CatchEvent([&](Event event) {
    if (event.is_character()) {
      char ch = event.character()[0];

      if (std::isdigit(ch)) {
        return false;
      } else if (ch == '.') {
        if (mileageStr.find('.') != std::string::npos) {
          return true;
        }
        return false;
      }
      return true;
    }
    return false;
  });

  Component input_power = Input(&powerStr, "Power (bhp)");
  input_power |= CatchEvent([&](Event event) {
    if (event.is_character()) {
      char ch = event.character()[0];

      if (std::isdigit(ch)) {
        return false;
      } else if (ch == '.') {
        if (powerStr.find('.') != std::string::npos) {
          return true;
        }
        return false;
      }
      return true;
    }
    return false;
  });

  Component input_fuel_tank_capacity =
      Input(&fuelTankCapacity, "Fuel Tank Capacity (liters)");
  input_fuel_tank_capacity |= CatchEvent([&](Event event) {
    if (event.is_character()) {
      char ch = event.character()[0];

      if (std::isdigit(ch)) {
        return false;
      } else if (ch == '.') {
        if (fuelTankCapacity.find('.') != std::string::npos) {
          return true;
        }
        return false;
      }
      return true;
    }
    return false;
  });

  Component input_seating_capacity =
      Input(&seatingCapacity, "Seating Capacity");
  input_seating_capacity |= CatchEvent([&](Event event) {
    return event.is_character() && !std::isdigit(event.character()[0]);
  });

  Component input_num_of_doors = Input(&numOfDoors, "Number of Doors");
  input_num_of_doors |= CatchEvent([&](Event event) {
    return event.is_character() && !std::isdigit(event.character()[0]);
  });
  Component input_engine_capacity =
      Input(&engineCapacity, "Engine Capacity (cc)");
  input_engine_capacity |= CatchEvent([&](Event event) {
    if (event.is_character()) {
      char ch = event.character()[0];

      if (std::isdigit(ch)) {
        return false;
      } else if (ch == '.') {
        if (engineCapacity.find('.') != std::string::npos) {
          return true;
        }
        return false;
      }
      return true;
    }
    return false;
  });

  Component dropdown_cartype =
      Dropdown(&cartype, &cartypeIndex) | size(WIDTH, EQUAL, 30);

  auto style = ButtonOption::Animated(Color::Default, Color::GrayDark,
                                      Color::Default, Color::White);
  Component button_submit = Button(
      "Submit",
      [&] {
        basePrice = stod(basePriceStr);
        mileage = stod(mileageStr);
        power = stod(powerStr);
        int d = stoi(numOfDoors);
        int sc = stoi(seatingCapacity);
        int fc = stod(fuelTankCapacity);
        int ec = stod(engineCapacity);

        Car tempCar(modelName, model, ct[cartypeIndex]);
        tempCar.setBasePrice(basePrice)
            .setMilagePower(mileage, power)
            .setDoorSeatingCap(d, sc)
            .setFuelEngineCap(fc, ec);

        if (!tempCar.isValid()) {
          return;
        }

        brandNewCar = new NewCar(tempCar);

        while (colors != "" && colors.find(",") != std::string::npos) {
          brandNewCar->pushColors(colors.substr(0, colors.find(",")));
          colors = colors.substr(colors.find(",") + 1);
        }
        if (colors != "") brandNewCar->pushColors(colors);

        for (auto variant : v) {
          if (!variant->build()) {
            delete brandNewCar;
            brandNewCar = nullptr;
            return;
          }

          brandNewCar->pushVariant(variant->getVariant());
        }

        screen.Exit();
        return;
      },
      style);

  auto component = Container::Vertical({
      input_model_name,
      input_model,
      input_colors,
      dropdown_cartype,
      input_base_price,
      input_mileage,
      input_power,
      input_fuel_tank_capacity,
      input_seating_capacity,
      input_num_of_doors,
      input_engine_capacity,
  });

  // Render the component
  auto basicInfoTab = Renderer(component, [&] {
    return vbox({window(
        text("New Car Info"),
        vbox({
            hbox(text("Model Name                 : "),
                 input_model_name->Render()),
            hbox(text("Model                      : "), input_model->Render()),
            hbox(text("Colors                     : "), input_colors->Render()),
            hbox(text("Car Type                   : "),
                 dropdown_cartype->Render()),
            hbox(text("Base Price                 : "),
                 input_base_price->Render()),
            separator(),
            hbox(text("Mileage                    : "),
                 input_mileage->Render()),
            hbox(text("Power (bhp)                : "), input_power->Render()),
            separator(),
            hbox(text("Fuel Tank Capacity (liters): "),
                 input_fuel_tank_capacity->Render()),
            hbox(text("Seating Capacity           : "),
                 input_seating_capacity->Render()),
            hbox(text("Number of Doors            : "),
                 input_num_of_doors->Render()),
            hbox(text("Engine Capacity (cc)       : "),
                 input_engine_capacity->Render()),
        }))});
  });

  /// Variants Tab
  auto basicVariant = new VariantManager("Base Variant");
  v.push_back(basicVariant);
  auto tab_selection =
      Menu(&tab_entries, &tab_index, MenuOption::HorizontalAnimated());
  auto tab_content =
      Container::Tab({basicInfoTab, basicVariant->getComponent()}, &tab_index);

  // Global Button
  auto quitBut = Button(" x ", [&] { screen.Exit(); }, style);
  auto varBut = Button(
      " + ",
      [&] {
        auto newComp = new VariantManager("Variant ", v.at(v.size() - 1));
        v.push_back(newComp);
        tab_entries.push_back(newComp->getVarName() == "Variant 1"
                                  ? " Base Variant "
                                  : " " + newComp->getVarName() + " ");
        tab_content->Add({newComp->getComponent()});
        tab_content->SetActiveChild(newComp->getComponent());
      },
      style);

  auto main_container = Container::Vertical({
      Container::Horizontal({tab_selection, varBut, button_submit, quitBut}),
      tab_content,
  });

  auto main_renderer = Renderer(main_container, [&] {
    return vbox({
        text("Register New Car") | bold | hcenter,
        hbox({tab_selection->Render() | flex, varBut->Render(),
              button_submit->Render(), quitBut->Render()}),
        tab_content->Render() | flex,
    });
  });

  screen.Loop(main_renderer);

  return brandNewCar;
}
