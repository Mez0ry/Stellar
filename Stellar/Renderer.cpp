#include "Renderer.hpp"

#include "Texture.hpp"
#include "Surface.hpp"

#include "Text.hpp"
#include "Vector.hpp"
#include "Logger.hpp"

Renderer::Renderer(const Base::Ref<Window> window, int index, uint32_t flags) : m_Renderer(nullptr) {
  CreateRenderer(*window,index,flags);
}

Renderer::Renderer(Window& window, int index, uint32_t flags) : m_Renderer(nullptr) {
  CreateRenderer(window,index,flags);
}

Renderer::~Renderer() {
  if (m_Renderer) {
    SDL_DestroyRenderer(m_Renderer);
  }
}

void Renderer::CreateRenderer(Window& window,int index,uint32_t flags){
  m_Renderer = SDL_CreateRenderer(window, index, flags);
  if (m_Renderer == NULL) {
    STELLAR_CORE_CRITICAL("Renderer::CreateRenderer(Window& window,int index,uint32_t flags), Failed to create renderer, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }else{
    STELLAR_CORE_INFO("Renderer successfully created, the index of the initialized rendering driver: {0}",index);
    window.CreateWindowSurface();
  }
}

void Renderer::RenderClear() { 
  if(SDL_RenderClear(m_Renderer)){
    STELLAR_CORE_ERROR("Renderer::RenderClear, Failed to render clear, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}

void Renderer::RenderFlush() { 
  if(SDL_RenderFlush(m_Renderer)){
    STELLAR_CORE_ERROR("Renderer::SDL_RenderFlush, Failed to render flush, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  } 
}

void Renderer::RenderPresent() { 
  SDL_RenderPresent(m_Renderer); 
}

void Renderer::SetRenderDrawColor(const Color &color) {
  if(SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a)){
    STELLAR_CORE_ERROR("Renderer::SetRenderDrawColor, Failed to set renderer draw color, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}

void Renderer::Render(const Texture &texture) {
  if(SDL_RenderCopy(m_Renderer,texture,texture.GetRect<SourceRect>(),texture.GetRect<DestRect>())){
    STELLAR_CORE_ERROR("Renderer::Renderer(const Texture& texture), Failed to render texture, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}

void Renderer::Render(const Texture &texture, const double angle, const SDL_Point *center, const SDL_RendererFlip flip) {
  if(SDL_RenderCopyEx(m_Renderer,texture,texture.GetRect<SourceRect>(),texture.GetRect<DestRect>(),angle,center,flip)){
    STELLAR_CORE_ERROR("Renderer::Renderer(const Texture& texture, args ...), Failed to render texture, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}

void Renderer::BlitSurface(Surface &src,SDL_Surface* dst){
  if(SDL_BlitSurface(src,src.GetRect<SourceRect>(),dst,src.GetRect<DestRect>())){
    STELLAR_CORE_ERROR("Renderer::BlitSurface(const Surface& src,SDL_Surface* dst), Failed to blit surface, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}

void Renderer::ScaledSurface(Surface& src,SDL_Surface* dst){
  if(SDL_BlitScaled(src,src.GetRect<SourceRect>(),dst,src.GetRect<DestRect>())){
    STELLAR_CORE_ERROR("Renderer::ScaledSurface(Surface& src,SDL_Surface* dst), Failed to blit surface, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}