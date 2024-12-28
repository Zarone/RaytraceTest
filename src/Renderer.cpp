#include <iostream>
#include "../include/Renderer.hpp"

Renderer::Renderer(int width, int height) {
  this->width = width;
  this->height = height;
  
  // SDL init
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    exit(1);
  }

  // create SDL window
  this->window = SDL_CreateWindow("Window",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    this->width * 4,
    this->height * 4,
    SDL_WINDOW_RESIZABLE
  );

  if (this->window == NULL) {
    SDL_Log("Unable to create window: %s", SDL_GetError());
    exit(1);
  }

  // create renderer
  this->renderer = SDL_CreateRenderer(
    window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
  if (this->renderer == NULL) {
    SDL_Log("Unable to create renderer: %s", SDL_GetError());
    exit(1);
  }
  
  SDL_RenderSetLogicalSize(renderer, this->width, this->height);

  // create texture
  this->texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_RGBA32,
    SDL_TEXTUREACCESS_STREAMING,
    this->width,
    this->height
  );
  if (this->texture == NULL) {
    SDL_Log("Unable to create texture: %s", SDL_GetError());
    exit(1);
  }
}

void Renderer::sendPixelsToRenderer(uint8_t* pixels) {
  // update texture with new data
  int texture_pitch = 0;
  void* texture_pixels = NULL;
  if (SDL_LockTexture(this->texture, NULL, &texture_pixels, &texture_pitch) != 0) {
    SDL_Log("Unable to lock texture: %s", SDL_GetError());
  }
  else {
    memcpy(texture_pixels, pixels, texture_pitch * this->height);
  }
  SDL_UnlockTexture(this->texture);
}

void Renderer::render() {
  // render on screen
  SDL_RenderClear(this->renderer);
  SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
  SDL_RenderPresent(this->renderer);

  std::cout << "Finished Rendering" << std::endl;
}

void Renderer::keepOpen(Scene s) {
  bool closing = false;
  SDL_Event e;
  while (!closing) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        closing = true;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;

        std::cout << e.button.x << ", " << e.button.y << std::endl;
        
        // coordinates on lens
        float u = s.l + (s.r-s.l)*(x+0.5)/width;
        float v = s.t + (s.b-s.t)*(y+0.5)/height;
        
        // math setup
        Vector3 basis_w = Vector3(1, 0, 0);

        Vector3 basis_u = s.up.cross(basis_w);
        basis_u = basis_u.divide_by(basis_u.magnitude());

        Vector3 basis_v = basis_w.cross(basis_u);

        Vector3 uu = basis_u.multiply_by(u);
        Vector3 vv = basis_v.multiply_by(v);

        Vector3 ww = basis_w.multiply_by(-s.focalLength);
        Vector3 rayDirection = ww.add(uu).add(vv);

        std::cout << "Collission: " << s.collissionCheckAll(rayDirection, s.cameraPosition, NULL, NULL) << std::endl;
      }
    }
  }
}

Renderer::~Renderer() {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
