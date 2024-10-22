#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

int main(void) {
  using namespace ftxui;

  // Define the document
  Element document = hbox({
      text("left") | border,
      text("middle") | border,
      text("right") | border,
  });

  Element win = window(text("Adrien Duport"), text("Cool."));

  auto screen = Screen::Create(Dimension::Full(),       // Width
                               Dimension::Fit(document) // Height
  );

  //  Render(screen, document);
  //  screen.Print();

  std::cout << "Hello>\n";

  Render(screen, win);
  screen.Print();

  return EXIT_SUCCESS;
}
