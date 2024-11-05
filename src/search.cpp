#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>

#include "../include/Car.h"
#include "../include/UI.h"
#include "../include/utils.h"

class SearchResultRender {
 public:
  SearchResultRender(std::string& s) {
    m = s;

    renderer = Renderer([&] {
      return vbox({
          text(m),
      });
    });
  }

  Component& getComponent() { return renderer; }

 protected:
  std::string m;
  Component renderer;
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
      SearchResultRender* r = new SearchResultRender(car.modelName);
      (*renderer)->Add(r->getComponent());
    }

    return this->renderer;
  }

  CarSearchEngine& modelName(std::string s) {
    utils::trim(s);
    utils::toLowerCase(s);

    if (s.length() <= this->modelNameLen)
      resultVector.clear();

    if (!resultVector.empty()) {
      for (auto it = resultVector.begin(); it != resultVector.end();) {
        std::string cmpStr = it->modelName;
        std::string cmpStr2 = it->model;
        if (
          utils::toLowerCase(cmpStr).find(s) == std::string::npos &&
          utils::toLowerCase(cmpStr2).find(s) == std::string::npos
        )
          it = resultVector.erase(it);
        else
          ++it;
      }
    } else {
      for (auto car : inventoryNewCar) {
        std::string cmpStr = car.modelName;
        std::string cmpStr2 = car.model;
        if (
          utils::toLowerCase(cmpStr).find(s) != std::string::npos ||
          utils::toLowerCase(cmpStr2).find(s) != std::string::npos
        ) {
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
      Input(&modelName, "Model Name or Model", InputOption{
      .on_change = [&]() {
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
                input_model_name->Render() | size(WIDTH, EQUAL, 20) | flex,
            }),
        }),

        searchResults->Render() | vscroll_indicator | frame | border | flex,
    });
  });

  screen.Loop(mainRenderer);

  return 0;
}
