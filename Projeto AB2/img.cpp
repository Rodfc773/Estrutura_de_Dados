#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  SDL_Window *window;
  SDL_Surface *screenSurface;
  SDL_Init(SDL_INIT_VIDEO);
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "Erro: " << SDL_GetError() << endl;
    SDL_Quit();
  }

  window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
  if (!window) {
  cout << "Erro: " << SDL_GetError() << endl;
  SDL_Quit();
  }
  screenSurface = SDL_GetWindowSurface(window);
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format,0xff, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  
  SDL_SetRenderDrawColor(renderer, 127, 0, 127, 255);
  SDL_Rect rect = {350, 250, 100, 100};
  SDL_RenderFillRect(renderer, &rect);

  SDL_Delay(5000);
  SDL_FreeSurface(screenSurface);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}