#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "config.h"
#include <fstream>
#include <sstream>


int main() {
  std::size_t speed;
  TxtConfig *tc = new TxtConfig("../src/parameter.txt");
  speed=tc->Read();
  delete tc;

  std::size_t kFramesPerSecond{param};
  std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  //Controller controller;
  std::shared_ptr<Controller> controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, std::move(renderer), kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}
