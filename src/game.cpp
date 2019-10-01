#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>
#include <mutex>
#include <algorithm>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(std::make_shared<Snake>(grid_width, grid_height)),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height))
{

  std::vector<std::future<void>> futures;
  for (int i = 0; i < 10 - foods.size(); i++)
  {
    futures.emplace_back(std::async(std::launch::async, &Game::PlaceFood, this));
  }

  ready = true;

  _cond.notify_all();
  std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
    ftr.wait();
  });

  std::cout << "foods size " << foods.size() << std::endl;
}

void Game::Run(std::shared_ptr<Controller> const controller, Renderer renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  std::shared_ptr<Snake> snake1(snake);

  std::cout << "snake1 size " << snake1->size << std::endl;

  std::cout << "snake1 alive " << snake1->alive << std::endl;
  std::cout << "snake1 speed " << snake1->speed << std::endl;

  auto t1 = std::chrono::high_resolution_clock::now();
  while (running)
  {
    frame_start = SDL_GetTicks();

    controller->HandleInput(running, *snake1);
    Update();

    renderer.Render(*snake1, foods);

    frame_end = SDL_GetTicks();

    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    
    if (frame_end - title_timestamp >= 1000)
    {
      auto t2 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
      // renderer.UpdateWindowTitle(score, frame_count);
      renderer.UpdateWindowTitle<int> (score, frame_count, int(fp_ms.count()/1000) );
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood()
{
  std::unique_lock<std::mutex> uLock(_mutex);
  _cond.wait(uLock, [this] { return ready; });
  int x, y;

  x = random_w(engine);
  y = random_h(engine);

  if (!snake->SnakeCell(x, y))
  {
    food.x = x;
    food.y = y;
    foods.push_back(food);
  }
}

void Game::Update()
{
  if (!snake->alive)
    return;

  snake->Update();
  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);

  // Check if there's food over here
  int index = 0;
  for (SDL_Point const &food2 : foods)
  {
    if (food2.x == new_x && food2.y == new_y)
    {

      score++;
      foods.erase(foods.begin() + index);

      std::vector<std::future<void>> futures;
      for (int i = 0; i < 10 - foods.size(); i++)
      {
        futures.emplace_back(std::async(std::launch::async, &Game::PlaceFood, this));
      }

      ready = true;

      _cond.notify_all();
      std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr) {
        ftr.wait();
      });

      snake->GrowBody();
      snake->speed += 0.02;
      break;
    }
    index++;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }