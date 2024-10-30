// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>   // for filler, text, hbox, vbox
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include <iostream>
#include <memory>  // for allocator
#include <string>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/node.hpp"      // for Render
#include "ftxui/screen/color.hpp"  // for ftxui
using namespace ftxui;

class VariantManager {
 public:
  VariantManager() : variantCount(0) {
    // Create the button to add new variants
    newVariantButton = Button(
        " + Add Variant ",
        [&] {
          if (variantCount < 10) {  // Limit to 10 windows
            variantCount++;         // Increment the count
            Render();               // Trigger re-rendering
          }
        },
        ButtonOption::Ascii());

    // Create the main vertical container for the variants
    variantComp = Container::Vertical({newVariantButton});
    renderer = Renderer(variantComp, [&] {
      std::vector<Element> windows;
      // Create the variant windows based on the count
      for (int i = 1; i <= variantCount; ++i) {
        auto win = window(text("Variant " + std::to_string(i)), vbox({})) |
                   vscroll_indicator;
        windows.push_back(win);
      }
      return vbox({hbox("", newVariantButton->Render()) | center,
                   vbox(windows) | vscroll_indicator | frame});
    });
  }

  Component GetComponent() { return renderer; }

 private:
  int variantCount;            // Counter for the number of variants
  Component newVariantButton;  // Button to add new variants
  Component variantComp;       // Vertical container for variants
  Component renderer;          // Renderer for the variant manager

  void Render() {
    variantComp->Render();  // Trigger re-rendering
  }
};

int regCar() {
  auto screen = ScreenInteractive::Fullscreen();

  int tab_index = 0;
  std::vector<std::string> tab_entries = {
      " Basic Details ",
      " Car Variants ",
  };

  /*
    " Safety Features ",
      " Comfort Features ",
      " Technical Features ",
    " Build Features ",
   *
      * */

  // The data:
  //  std::string modelName;
  //  std::string model;
  //
  //  double basePrice;
  //  double mileage;
  //  double power;  // in bhp?
  //
  //  int fuelTankCapacity;
  //  int seatingCapacity;
  //  int numOfDoors;
  //  int engineCapacity;  // in cc
  //
  //  std::string first_name;
  //  std::string last_name;
  //  std::string password;
  //  std::string phoneNumber;

  std::string modelName, model;
  std::string basePriceStr, mileageStr, powerStr;  // Use strings for input
  double basePrice, mileage, power;
  std::string fuelTankCapacity, seatingCapacity, numOfDoors, engineCapacity;

  Component input_model_name = Input(&modelName, "Model Name");
  Component input_model = Input(&model, "Model");

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

  auto style = ButtonOption::Animated(Color::Default, Color::GrayDark,
                                      Color::Default, Color::White);
  Component button_submit = Button(
      "Submit",
      [&] {
        // Validate and convert string inputs to double
        try {
          basePrice = std::stod(basePriceStr);
          mileage = std::stod(mileageStr);
          power = std::stod(powerStr);

          // Print or handle the values (for debugging)
          std::cout << "Model: " << modelName << ", " << model << "\n";
          std::cout << "Base Price: " << basePrice << "\n";
          std::cout << "Mileage: " << mileage << "\n";
          std::cout << "Power: " << power << "\n";
          std::cout << "Fuel Tank Capacity: " << fuelTankCapacity << "\n";
          std::cout << "Seating Capacity: " << seatingCapacity << "\n";
          std::cout << "Number of Doors: " << numOfDoors << "\n";
          std::cout << "Engine Capacity: " << engineCapacity << "\n";
        } catch (const std::invalid_argument&) {
          // Handle invalid input
          std::cout << "Invalid input for base price, mileage, or power.\n";
        }
      }
      //  ,ButtonOption::Ascii()
      ,
      style);

  auto component = Container::Vertical({
      input_model_name,
      input_model,
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
            hbox(text("Base Price                 : "),
                 input_base_price->Render()),
            hbox(text("Mileage                    : "),
                 input_mileage->Render()),
            hbox(text("Power (bhp)                : "), input_power->Render()),
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
  auto basicVariant = new VariantManager();
  auto tab_selection =
      Menu(&tab_entries, &tab_index, MenuOption::HorizontalAnimated());
  auto tab_content =
      Container::Tab({basicInfoTab, basicVariant->GetComponent()}, &tab_index);

  // Global Button
  auto varBut = Button(
      " + ",
      [&] {
        tab_entries.push_back(" Pus Kar " +
                              std::to_string(tab_content->ChildCount()));
        auto newComp = new VariantManager();
        tab_content->Add({newComp->GetComponent()});
        tab_content->SetActiveChild(newComp->GetComponent());
      },
      style);

  auto main_container = Container::Vertical({
      Container::Horizontal({tab_selection, varBut, button_submit}),
      tab_content,
  });

  auto main_renderer = Renderer(main_container, [&] {
    return vbox({
        text("Register New Car") | bold | hcenter,
        hbox({tab_selection->Render() | flex, varBut->Render(),
              button_submit->Render()}),
        tab_content->Render() | flex,
    });
  });

  screen.Loop(main_renderer);

  return 0;
}
