#include "Text.hpp"

Text::Text() noexcept : m_font(nullptr)
{
 
}

Text::Text(const Base::Ref<Renderer> renderer,const char* font_path,int font_size, const char* text,const Color& color) : m_Color(color)
{
  LoadFont(font_path,font_size);
  LoadText(renderer,text,m_Color);
}

Text::~Text() noexcept
{
   Reset();
}

Base::Ref<TTF_Font> Text::LoadFont(const char *path, int font_size)
{
  TTF_Font* font = TTF_OpenFont(path, font_size);
  m_font = Base::Ref<TTF_Font>(font,TTF_FontDeleter());
  if (m_font == nullptr)
  {
    STELLAR_CORE_ERROR("Text::LoadFont, Failed to open font, SDL_ttf Error: {0}, Failed at {1}:{2}", TTF_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
  return m_font;
}

Texture& Text::LoadText(const Base::Ref<Renderer> renderer,const char *text, const Color &color)
{
  Reset();
  m_Color = color;
  SDL_Surface * surface = TTF_RenderText_Solid(m_font.get(), text, color);
  if (surface == nullptr)
  {
    STELLAR_CORE_ERROR("Text::LoadText, Failed to create text surface, SDL_ttf Error: {0}, Failed at {1}:{2}", TTF_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
  
  m_Texture.ShareSDLTexture(Texture::CreateTextureFromSurface(renderer,surface));
  
  SDL_FreeSurface(surface);
  surface = nullptr;
  
  return m_Texture;
}

Texture& Text::LoadText(Renderer& renderer,const char *text, const Color &color){
  Reset();
  m_Color = color;
  SDL_Surface * surface = TTF_RenderText_Solid(m_font.get(), text, color);
  if (surface == nullptr)
  {
    STELLAR_CORE_ERROR("Text::LoadText, Failed to create text surface, SDL_ttf Error: {0}, Failed at {1}:{2}", TTF_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
  
  m_Texture.ShareSDLTexture(Texture::CreateTextureFromSurface(renderer,surface));
  
  SDL_FreeSurface(surface);
  surface = nullptr;
  
  return m_Texture;
}

void Text::ShareFont(Base::Ref<TTF_Font>&& font)
{
  this->m_font = std::move(font);
}

void Text::Reset()
{
  m_Texture.Reset();
}

void Text::ResetFont()
{
  if(m_font.unique()){
    m_font.reset();
    m_font = nullptr;
  }
}