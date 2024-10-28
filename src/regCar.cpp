// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <ftxui/component/component_options.hpp>
#include <ftxui/dom/elements.hpp>   // for filler, text, hbox, vbox
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include <memory>                   // for allocator

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/node.hpp"      // for Render
#include "ftxui/screen/color.hpp"  // for ftxui

int regCar() {
  using namespace ftxui;
  auto screen = ScreenInteractive::Fullscreen();

  int tab_index = 0;
  std::vector<std::string> tab_entries = {
      " Safety Features ", " Comfort Features ", " Technical Features ",
      " Build Features ",  " Car Variants ",     " Basic Details "};

  auto tab_selection =
      Menu(&tab_entries, &tab_index, MenuOption::HorizontalAnimated());

  screen.Loop(tab_selection);

  return 0;
}
