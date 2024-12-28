#pragma once
#include <SDL.h>
#include "../include/Scene.hpp"

class Renderer
{
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  int width;
  int height;
public:
  Renderer(int width, int height);
  void sendPixelsToRenderer(uint8_t* pixels);
  void render();
  void keepOpen(Scene s);
  ~Renderer();
};
