# CPPND: Capstone Snake Game 

This is a snake game which enables me to practice my c++ skills. I have tried what I learnt and applied it here. Every time, it will place 10 foods for sanke with concurrency, once snake eat one, then a new food will be placed randomly.

## Rubric Points

1. The project can be compiled by command : `cmake .. && make`and run it with command: `./SnakeGame`.
2. TxtConfig class is created in config.h to read config content from exteral file, which was called from main.cpp
3. HandleInput function in Controller class handle user's input to change snake's direction
4. All class constrctors were using initialization list
5. TxtConfig class is inheriated from parent class Config, which enable us to extent the config to other formats like json or yaml
6. UpdateWindowTitle function in Renderer class was overloadded with same function name but different parameters
7. Read and Update function in TxtConfig class overide the virutal function in Config class
8. void Renderer::UpdateWindowTitle(T score, T fps, T lastseconds) was templated and allows a generic parameter
9. void Renderer::Render(Snake const snake, std::vector<SDL_Point> &foods) function pass parameter foods as reference
10. TxtConfig *tc object in main.cpp was allocaed with new operator and was deleted later
11. Renderer renderer object in main.cpp will be destructed automatically after the main function returns
12. in snake.h,  copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined
13. In game.Run(controller, std::move(renderer), kMsPerFrame) function, the renderer object was initialized with move constructors
14. In void Game::Run(std::shared_ptr<Controller> const controller, Renderer renderer,std::size_t target_frame_duration) function, the shared_ptr was used in parameter.
15. In void Game::Update() function, multiple threads were used to place foods. Promise and future also get used.
16. In void Game::PlaceFood(), unique_lock was used to make sure there is no race when add food into foods vector.
17. In void Game::PlaceFood(),  condition_variable was used to wait until the status is in ready.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

