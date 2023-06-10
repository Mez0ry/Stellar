#ifndef __COLOR_HPP__
#define __COLOR_HPP__
#include <cstdint>
#include "SDL2/SDL_pixels.h"

struct Color{
  uint8_t r,g,b,a;

  Color() : r(0),g(0),b(0),a(0) {};
  Color(SDL_Color color) : r(color.a),g(color.g),b(color.b),a(color.a) {}
  Color(uint8_t r, uint8_t g, uint8_t b , uint8_t a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }

  ~Color() = default;

  operator SDL_Color() const{
    return SDL_Color{r,g,b,a};
  }
};
#endif //!__COLOR_HPP__