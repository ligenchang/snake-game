#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <iostream>
#include <thread>
#include <future>

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, std::vector<SDL_Point>  &foods);
  void UpdateWindowTitle(int score, int fps);
  template<class T>
  void UpdateWindowTitle(T score, T fps, T lastseconds);
  void RenderFood(SDL_Point* food);

  // Renderer& operator=(Renderer other)
  //   {
  //       screen_width=other.screen_width;
  //       screen_height=other.screen_height;
  //       grid_width=other.grid_width;
  //       grid_height=other.grid_height;
  //       sdl_window=other.sdl_window;
  //       sdl_renderer=other.sdl_renderer;
  //       return *this;
  //   }

  //   Renderer& operator=(Renderer&& other)
	// {
	// 	if (&other == this)
	// 		return *this;
 
	// 	  screen_width=std::move(other.screen_width);     
  //     screen_height=std::move(other.screen_height); 
  //     grid_width=std::move(other.grid_width); 
  //     grid_height=std::move(other.grid_height); 
  //     sdl_window=std::exchange(other.sdl_window, nullptr); 
  //     sdl_renderer=std::exchange(other.sdl_renderer, nullptr); 
 
	// 	return *this;
	// }

  Renderer(Renderer&& o) :
           screen_width(std::move(o.screen_width)), 
           screen_height(std::move(o.screen_height)),
           grid_width(std::move(o.grid_width)),
           grid_height(std::move(o.grid_height)),
           sdl_window(std::exchange(o.sdl_window, nullptr)),
           sdl_renderer(std::exchange(o.sdl_renderer, nullptr))
{}

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  bool ready = false;
  std::mutex _mutex;
  std::condition_variable _cond;

};

#endif