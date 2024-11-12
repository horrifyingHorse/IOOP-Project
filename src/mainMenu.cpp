#include <ftxui/component/mouse.hpp>
#include <functional>
#include <string>
#include <vector>

#include "../include/UI.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"

int mainMenuCustomer() {
  using namespace ftxui;

  auto screen = ScreenInteractive::Fullscreen();

  std::vector<std::string> entries = {"1. Explore Cars", "</ Exit"};
  int selected = 0;

  MenuOption option;
  option.on_enter = screen.ExitLoopClosure();
  auto menu =
      Menu(&entries, &selected, option) | border | size(WIDTH, EQUAL, 40);

  menu |= CatchEvent([&](Event event) {
    if (event.is_mouse() && event.mouse().button == Mouse::Left &&
        event.mouse().motion == Mouse::Released) {
      selected = event.mouse().y;
      screen.ExitLoopClosure()();
      return true;
    }
    return false;
  });

  Component page = Renderer(menu, [&] {
    return vbox({vbox({
                     menu->Render(),
                 }) |
                 hcenter | center | yflex

           }) |
           flex;
  });

  screen.Loop(page);

  return selected;
}

int mainMenuEmployee() {
  using namespace ftxui;

  auto screen = ScreenInteractive::Fullscreen();

  std::vector<std::string> entries = {"1. Register New Car",
                                      "2. Register Second Hand Car", "</ Exit"};
  int selected = 0;

  MenuOption option;
  option.on_enter = screen.ExitLoopClosure();
  auto menu =
      Menu(&entries, &selected, option) | border | size(WIDTH, EQUAL, 40);

  menu |= CatchEvent([&](Event event) {
    if (event.is_mouse() && event.mouse().button == Mouse::Left &&
        event.mouse().motion == Mouse::Released) {
      selected = event.mouse().y;
      screen.ExitLoopClosure()();
      return true;
    }
    return false;
  });

  Component page = Renderer(menu, [&] {
    return vbox({vbox({
                     menu->Render(),
                 }) |
                 hcenter | center | yflex}) |
           flex;
  });

  screen.Loop(page);

  return selected;
}

int mainMenuManager() {
  using namespace ftxui;

  auto screen = ScreenInteractive::Fullscreen();

  std::vector<std::string> entries = {"1. Employ new Employee",
                                      "2. Unemploy an Employee", "</ Exit"};
  int selected = 0;

  MenuOption option;
  option.on_enter = screen.ExitLoopClosure();
  auto menu =
      Menu(&entries, &selected, option) | border | size(WIDTH, EQUAL, 40);

  menu |= CatchEvent([&](Event event) {
    if (event.is_mouse() && event.mouse().button == Mouse::Left &&
        event.mouse().motion == Mouse::Released) {
      selected = event.mouse().y;
      screen.ExitLoopClosure()();
      return true;
    }
    return false;
  });

  Component page = Renderer(menu, [&] {
    return vbox({vbox({
                     menu->Render(),
                 }) |
                 hcenter | center | yflex}) |
           flex;
  });

  screen.Loop(page);

  return selected;
}
