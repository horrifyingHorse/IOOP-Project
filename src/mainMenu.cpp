// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <ftxui/component/mouse.hpp>
#include <functional>  // for function
#include <string>      // for string, basic_string, allocator
#include <vector>      // for vector

#include "ftxui/component/component.hpp"           // for Menu
#include "ftxui/component/component_options.hpp"   // for MenuOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive

int mainMenu() {
  using namespace ftxui;
  auto screen = ScreenInteractive::TerminalOutput();

  std::vector<std::string> entries = {
      "1. Register New Car",
      "2. Search a Car",
      "</ Exit"
  };
  int selected = 0;

  MenuOption option;
  option.on_enter = screen.ExitLoopClosure();
  auto menu = Menu(&entries, &selected, option);

  menu |= CatchEvent([&](Event event) {
    if (event.is_mouse() && event.mouse().button == Mouse::Left &&
        event.mouse().motion == Mouse::Released) {
      selected = event.mouse().y;
      screen.ExitLoopClosure()();
      return true;
    }
    return false;
  });

  screen.Loop(menu);

  return selected;
}
