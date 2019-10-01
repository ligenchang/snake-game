#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <iostream>
#include <memory>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(std::shared_ptr<Controller> const controller, Renderer renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  // Snake snake;
  std::shared_ptr<Snake> snake;
  SDL_Point food;
  std::vector<SDL_Point> foods; 

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
  std::mutex mtx;
  bool ready = false;
  std::mutex _mutex;
  std::condition_variable _cond;

};

#endif