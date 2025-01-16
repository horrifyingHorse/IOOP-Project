#include <ftxui/component/mouse.hpp>
#include <ftxui/dom/elements.hpp>
#include <functional>
#include <string>
#include <vector>

#include "../include/UI.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"

int profileSelect() {
  using namespace ftxui;

  auto screen = ScreenInteractive::Fullscreen();
  // clang-format off
  std::vector<std::string> profiles = {
    "Customer", "Employee", "Manager", "Exit"
  };
  // clang-format on
  int selected = 0;

  MenuOption option;
  option.on_enter = screen.ExitLoopClosure();
  auto menu =
      Menu(&profiles, &selected, option) | border | size(WIDTH, EQUAL, 40);
  menu |= CatchEvent([&](Event event) {
    if (event.is_mouse() && event.mouse().button == Mouse::Left &&
        event.mouse().motion == Mouse::Released) {
      selected = event.mouse().y;
      screen.ExitLoopClosure()();
      return true;
    }
    return false;
  });

  // clang-format off
  Component page = Renderer(menu, [&] {
    return vbox({
      vbox({
        text(" Select User Profile"), menu->Render()
      }) | hcenter | center | yflex
    }) | flex;
  });
  // clang-format on

  screen.Loop(page);
  return selected;
}
