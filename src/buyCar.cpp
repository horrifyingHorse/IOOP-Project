#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>

#include "../include/Humans.h"
#include "../include/UI.h"
#include "../include/utils.h"

void buyCar(NewCar &c) {
  auto screen = ScreenInteractive::Fullscreen();

  auto quitBut = Button(" x ", [&] { screen.Exit(); }, ButtonOption::Ascii());
  std::string name, address, phoneNumber, email;

  Component input_name = Input(&name, "Full Name");
  Component input_address = Input(&address, "Address");
  Component input_email = Input(&email, "Email");
  Component input_phoneNumber = Input(&phoneNumber, "Phone Number");
  input_phoneNumber |= CatchEvent([&](Event event) {
    return event.is_character() && !std::isdigit(event.character()[0]);
  });
  input_phoneNumber |= CatchEvent([&](Event event) {
    return event.is_character() && phoneNumber.size() > 10;
  });

  int color_entry = 0;
  Component color_dropdown = Dropdown(&c.colors, &color_entry);

  int variant_entry = 0;
  std::vector<std::string> variants = {};
  std::vector<double> cost = {};
  for (auto v : c.variants) {
    variants.push_back(v.getName());
    cost.push_back(v.getPrice());
  }
  Component variant_dropdown = Dropdown(&variants, &variant_entry);

  // clang-format off
  Component submit_button = Button(" Submit ", [&] {
    Customer cst;
    cst.updateDetails(
      name, address, phoneNumber, email,
      c.modelName, c.colors[color_entry],
      variants[variant_entry], cost[variant_entry]
    );

    if (!Customer::isValid(cst)) {
      return ;
    }

    Customer::storeReceipt(cst);
    screen.Exit();
  }, ButtonOption::Ascii());

  Component main_container = Container::Vertical({
    Container::Horizontal({submit_button, quitBut}),
    input_name,
    input_address,
    input_email,
    input_phoneNumber,
    color_dropdown,
    variant_dropdown,
  });

  Component main_renderer = Renderer(main_container, [&] {
    return vbox({
      window(
        text("Enter Details"), 
        vbox({
          hbox({
            text(utils::currentDate()) | flex,
            submit_button->Render(),
            quitBut->Render(),
          }),
          separatorLight(),
          hbox({
            text("Name      : "),
            input_name->Render(),
          }),
          hbox({
            text("Address   : "),
            input_address->Render(),
          }),
          hbox({
            text("Email     : "),
            input_email->Render(),
          }),
          hbox({
            text("Phone No. : "),
            input_phoneNumber->Render(),
          }) | size(WIDTH, EQUAL, 40),
          separatorEmpty(),
          hbox({
            text("Car Mode  : "),
            text(c.modelName),
          }),
          hbox({
            text("Car       : "),
            text(c.model),
          }),
          hbox({
            text("Color     : "),
            color_dropdown->Render(),
          }),
          hbox({
            text("Variant   : "),
            variant_dropdown->Render(),
          }),
          hbox({
            text("Cost      : "),
            text(utils::dtos(cost[variant_entry])),
          })
        })
      ) | center | flex 
    }) | flex;
  });
  // clang-format on

  screen.Loop(main_renderer);
}

void buyCar(SecondHandCar &c) {
  auto screen = ScreenInteractive::Fullscreen();

  auto quitBut = Button(" x ", [&] { screen.Exit(); }, ButtonOption::Ascii());
  std::string name, address, phoneNumber, email;

  Component input_name = Input(&name, "Full Name");
  Component input_address = Input(&address, "Address");
  Component input_email = Input(&email, "Email");
  Component input_phoneNumber = Input(&phoneNumber, "Phone Number");
  input_phoneNumber |= CatchEvent([&](Event event) {
    return event.is_character() && !std::isdigit(event.character()[0]);
  });
  input_phoneNumber |= CatchEvent([&](Event event) {
    return event.is_character() && phoneNumber.size() > 10;
  });

  // clang-format off
  Component submit_button = Button(" Submit ", [&] {
    Customer cst;

    cst.setPreOwned(c.prevOwner);
    cst.updateDetails(
      name, address, phoneNumber, email,
      c.modelName, c.colors, c.variant->getName(),
      c.variant->getPrice()
    );

    if (!Customer::isValid(cst)) {
      return ;
    }

    Customer::storeReceipt(cst);
    screen.Exit();
  }, ButtonOption::Ascii());

  Component main_container = Container::Vertical({
    Container::Horizontal({submit_button, quitBut}),
    input_name,
    input_address,
    input_email,
    input_phoneNumber,
  });

  Component main_renderer = Renderer(main_container, [&] {
    return vbox({
      window(
        text("Enter Details"),
        vbox({
          hbox({
            text(utils::currentDate()) | flex,
            submit_button->Render(),
            quitBut->Render(),
          }),
          separatorLight(),
          hbox({
            text("Name      : "),
            input_name->Render(),
          }),
          hbox({
            text("Address   : "),
            input_address->Render(),
          }),
          hbox({
            text("Email     : "),
            input_email->Render(),
          }),
          hbox({
            text("Phone No. : "),
            input_phoneNumber->Render(),
          }) | size(WIDTH, EQUAL, 40),
          separatorEmpty(),
          hbox({
            text("Car Mode  : "),
            text(c.modelName),
          }),
          hbox({
            text("Car       : "),
            text(c.model),
          }),
          hbox({
            text("Color     : "),
            text(c.colors)
          }),
          hbox({
            text("Variant   : "),
            text(c.variant->getName())
          }),
          hbox({
            text("Cost      : "),
            text(utils::dtos(c.variant->getPrice()))
          })
        })
      ) | center | flex 
    }) | flex;
  });
  // clang-format on

  screen.Loop(main_renderer);
}
