#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include <iostream>
#include <thread>
#include <future>


class Animal {
public:
  virtual void Update() = 0;
  virtual void GrowBody() = 0;
};

class Snake : Animal{
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  ~Snake();

  void Update() override;

  void GrowBody() override;
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

  Snake(Snake&& o) :
           direction(std::move(o.direction)),   
           body(std::move(o.body)),
           speed(std::exchange(o.speed, 0.0f)),
           size(std::exchange(o.size, 0)),
           alive(std::exchange(o.alive, false)),
           head_x(std::exchange(o.head_x, 0.0f)),
           head_y(std::exchange(o.head_y, 0.0f)),
           growing(std::exchange(o.growing, false)),
           grid_width(std::exchange(o.grid_width, 0)),
           grid_height(std::exchange(o.grid_height, 0))
{}

  Snake(Snake& o) :
           direction(o.direction),   
           body(o.body),
           speed(o.speed),
           size(o.size),
           alive(o.alive),
           head_x(o.head_x),
           head_y(o.head_y),
           growing(o.growing),
           grid_width(o.grid_width),
           grid_height(o.grid_height)
{}


Snake& operator=(Snake o){
           direction=o.direction;  
           body=o.body;
           speed=o.speed;
           size=o.size;
           alive=o.alive;
           head_x=o.head_x;
           head_y=o.head_y;
           growing=o.growing;
           grid_width=o.grid_width;
           grid_height=o.grid_height;
}

    Snake& operator=(Snake&& other)
	{
		if (&other == this)
			return *this;
 
		  direction=std::move(other.direction);    
      body=std::move(other.body);   
      speed=std::move(other.speed);   
      size=std::move(other.size);   
      alive=std::move(other.alive);   
      head_x=std::move(other.head_x);   
      head_y=std::move(other.head_y);   
      growing=std::move(other.growing);   
      grid_width=std::move(other.grid_width);    
      grid_height=std::move(other.grid_height); 
 
 
		return *this;
	}

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif