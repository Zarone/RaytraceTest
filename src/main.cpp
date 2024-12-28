#include <stdio.h>
#include <stdbool.h>

#include "../include/Renderer.hpp"
#include "../include/Imager.hpp"

#define WIDTH 200
#define HEIGHT 200

int main(int argc, char **argv) {

  Renderer myRenderer = Renderer(WIDTH, HEIGHT);

  // array of pixels
  uint8_t pixels[WIDTH * HEIGHT * 4] = {0};
  Scene s = myScene(WIDTH, HEIGHT);
  s.makeImage(pixels);

  myRenderer.sendPixelsToRenderer(pixels);
  myRenderer.render();
  myRenderer.keepOpen(s);

  return 0;
}
