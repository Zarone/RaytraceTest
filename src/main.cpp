#include <stdio.h>
#include <stdbool.h>

#include "../include/Renderer.hpp"
#include "../include/Imager.hpp"

#define WIDTH 500
#define HEIGHT 500

int main(int argc, char **argv) {

  Renderer myRenderer = Renderer(WIDTH, HEIGHT);

  // array of pixels
  uint8_t pixels[WIDTH * HEIGHT * 4] = {0};
  makeImage(pixels, WIDTH, HEIGHT);

  myRenderer.sendPixelsToRenderer(pixels);
  myRenderer.render();
  myRenderer.keepOpen();

  return 0;
}
