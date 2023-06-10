#include "Surface.hpp"

Surface::Surface() noexcept : m_Surface(nullptr){
   
}

Surface::Surface(SDL_Surface* surface) : m_Surface(nullptr){
  m_Surface = std::move(SurfaceCreator(surface).CreateSurface());
}

Surface::Surface(const std::string& path) : m_Surface(nullptr){
  LoadSurface(path);
}

Surface::~Surface() noexcept{
  Reset();
}

Base::Ref<SDL_Surface> Surface::LoadSurface(const std::string& image_path){
  Reset();
  m_Surface = std::move(SurfaceCreator(image_path).CreateSurface());
  
  return m_Surface;
}

void Surface::ShareSDLSurface(const Surface& surface){
  Reset();
  m_Surface = surface.m_Surface;
}

void Surface::ShareSDLSurface(const Base::Ref<SDL_Surface>& surface){
  Reset();
  m_Surface = surface;
}

void Surface::Reset(){
  if (m_Surface != nullptr) {
    m_Surface.reset();
    m_Surface = nullptr;
  }
}