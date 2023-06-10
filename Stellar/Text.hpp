#ifndef SnakeGame_FONT_MANAGER_HPP
#define SnakeGame_FONT_MANAGER_HPP

#include "Vector.hpp"
#include "Base.hpp"

#include "SDL2/SDL_ttf.h"
#include "Texture.hpp"

#include "Color.hpp"

struct TTF_FontDeleter {
  void operator()(TTF_Font *font) {
    if (font != nullptr) {
      TTF_CloseFont(font);
      font = nullptr;
    }
  }
};

class Text{
public:
  Text() noexcept;
  Text(const Base::Ref<Renderer> renderer,const char *font_path, int font_size, const char *text, const Color &color);
  Text(Renderer& renderer,const char *font_path, int font_size, const char *text, const Color &color);
  ~Text() noexcept;

  Text(Text &&other) {
    this->m_font = std::move(other.m_font);
    this->m_Texture = std::move(other.m_Texture);
    this->m_Color = std::move(other.m_Color);
  }

  Text& operator=(const Text& other){
    if(this == &other){
      return (*this);
    }
    this->m_font = other.m_font;
    this->m_Texture = other.m_Texture;

    this->m_Color = other.m_Color;
    return (*this);
  }

  Text& operator=(Text&& other){
    if(this == &other){
      return (*this);
    }
    this->m_font = std::move(other.m_font);
    this->m_Texture = std::move(other.m_Texture);
    this->m_Color = std::move(other.m_Color);
    return (*this);
  }
  
  Texture* operator->(){
    return &m_Texture;
  }

  operator Texture&() noexcept{
    return m_Texture;
  }

  Base::Ref<TTF_Font> LoadFont(const char *path, int font_size);
  Texture& LoadText(const Base::Ref<Renderer> renderer,const char *text, const Color &color);
  Texture& LoadText(Renderer& renderer,const char *text, const Color &color);

  void ShareFont(Base::Ref<TTF_Font>&& font);
  void Reset();
  void ResetFont();

  Texture& GetTextTexture() {return m_Texture;}
  const Texture& GetTextTexture() const {return m_Texture;}
  
private:
  Base::Ref<TTF_Font> m_font;
  Texture m_Texture;
  SDL_Color m_Color;
};
#endif //! SnakeGame_FONT_MANAGER_HPP