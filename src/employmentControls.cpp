#include <string>
#include <utility>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include "../include/UI.h"
#include "../include/Humans.h"

bool managerLogin(Manager& m) {
  auto screen = ScreenInteractive::Fullscreen();

  bool isValid = false;

  std::string username = "";
  std::string password = "";

  auto quitBut = Button(" x ", [&] { screen.Exit(); }, ButtonOption::Ascii());

  Component input_username = Input(&username, " Username ") | size(WIDTH, EQUAL, 10);
  Component input_password = Input(&password, " Password ") | size(WIDTH, EQUAL, 10);

  Component submit_button = Button(" Submit ", [&] {
    isValid = m.login(username, password);
    if (isValid) {
      screen.Exit();
    }
  }, ButtonOption::Ascii());

  Component main_container = Container::Vertical({
    quitBut, input_username, input_password, submit_button
  });

  Component mainRenderer = Renderer(main_container, [&] {
    return vbox({
      hbox({
        text(" Enter Credentials:") | flex,
        quitBut->Render()
      }) | size(WIDTH, EQUAL, 40),
      vbox({
        hbox({
          text("Username  :  "),
          input_username->Render(),
        }) | center,
        hbox({
          text("Password  :  "),
          input_password->Render(),
        }) | center,
        hbox({text("")}),
        submit_button->Render() | center,
      }) |  center | border | size(WIDTH, EQUAL, 40),
    }) | yflex | center | hcenter;
  });

  screen.Loop(mainRenderer);

  return isValid;
}

void addEmployee(Manager& m) {
  auto screen = ScreenInteractive::Fullscreen();

  std::string empName = "";
  std::string empID = "";

  auto quitBut = Button(" x ", [&] { screen.Exit(); }, ButtonOption::Ascii());
  Component submit_button = Button(" Submit ", [&] {
    if(m.addEmployee(empName, empID)) {
      screen.Exit();
    }
  }, ButtonOption::Ascii());

  Component input_empName = Input(&empName, " Employee Name ");
  Component input_empID = Input(&empID, " Employee ID ");

  Component main_container = Container::Vertical({
    Container::Horizontal({submit_button, quitBut}),
    input_empName, input_empID
  });

  Component main_renderer = Renderer(main_container, [&] {
    return vbox({vbox({
      window(
        text("Employee Details"),
        vbox({
          hbox({
            text(" ") | flex,
            submit_button->Render(),
            quitBut->Render()
          }),
          separatorLight(),
          hbox({
            text("Employee Name     : "),
            input_empName->Render()
          }),
          hbox({
            text("Employee ID       : "),
            input_empID->Render()
          }),
          hbox({text(" ")})
        }) | size(WIDTH, EQUAL, 40)
      ),
    }) | center | hcenter | yflex
    }) | flex;
  });

  screen.Loop(main_renderer);
}

void removeEmployee(Manager& m) {
  auto screen = ScreenInteractive::Fullscreen();
  std::vector<std::pair<std::string, std::string>> empList = m.getAllEmployees();
  bool states[empList.size()];


  auto quitBut = Button(" x ", [&] { screen.Exit(); }, ButtonOption::Ascii());
  Component submit_button = Button(" Submit ", [&] {
    int removeCount = 0;
    for (int i = 0; i < empList.size(); i++) {
      if (states[i]) {
        m.removeEmployee(empList[i].first);
        removeCount++;
      }
    }
    screen.Exit();
  }, ButtonOption::Ascii());

  auto container = Container::Vertical({});
  for (int i = 0; i < empList.size(); ++i) {
    states[i] = false;
    container->Add(
        Checkbox(utils::to50(empList[i]),
                 &states[i]));
  }

  Component main_container = Container::Vertical({
    Container::Horizontal({submit_button, quitBut}),
    container
  });

  auto renderer = Renderer(main_container, [&] {
    return vbox({
      hbox({
        text(" Select to  U n E m p l o y !") | blink | flex,
        submit_button->Render(),
        quitBut->Render()
      }),
      vbox({
        container->Render() | vscroll_indicator | frame |
             flex | border
      }) | flex | size(WIDTH, EQUAL, 50) 
    }) | flex | center;
  });

  screen.Loop(renderer);
}

