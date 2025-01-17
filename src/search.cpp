#include <cstdio>
#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "../include/Car.h"
#include "../include/UI.h"

int searchCars(std::vector<NewCar>& inventoryNewCar,
               std::vector<SecondHandCar>& inventorySHCar) {
  auto screen = ScreenInteractive::Fullscreen();

  auto searchResults = Container::Vertical({});

  CarSearchEngine engine(inventoryNewCar, inventorySHCar, &searchResults);

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
  auto quitBut = Button(" x ", [&] { screen.Exit(); }, ButtonOption::Ascii());

  int indexUsage = 0;
  std::vector<std::string> usage = {"Brand New Cars", "Pre-Owned Cars"};
  auto usageDropdown = Dropdown(&usage, &indexUsage) | size(WIDTH, EQUAL, 20);

  // clang-format off
  Component applyButton = Button(" Apply ", [&] {
    engine.setMode(indexUsage);
    std::cout << indexUsage;
  }, style);

  Component input_model_name = Input(
    &modelName,
    "Model Name or Model",
    InputOption{
      .multiline = false,
      .on_change = [&]() {
        engine.modelName(modelName);
        engine.render();
      },
  });

  auto searchParams = Container::Horizontal({
      input_model_name,
  });

  auto mainContainer = Container::Vertical({
      quitBut,
      Container::Horizontal({usageDropdown, applyButton}),
      searchParams,
      searchResults,

  });

  auto mainRenderer = Renderer(mainContainer, [&] {
    return vbox({
      hbox({
        text("./cars") | dim | bold | hcenter | flex,
        quitBut->Render(),
      }),
      separatorDouble(),
        vbox({
          hbox({
            usageDropdown->Render(),
            applyButton->Render(),
          }),
          hbox({
            text("Model Name: "),
            input_model_name->Render() | size(WIDTH, EQUAL, 20) | flex,
          }),
      }),
      separatorLight(),
      searchResults->Render() | vscroll_indicator | frame | flex,
    }) | border;
  });
  // clang-format on

  screen.Loop(mainRenderer);

  return 0;
}
