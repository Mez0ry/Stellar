#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

#include "Vector.hpp"
#include "Base.hpp"
#include "Renderer.hpp"

#include "ObjectSize.hpp"
#include "SourceDestRect.hpp"

#include <cstring>

#include "Logger.hpp"

class Renderer;

struct PixelFormatGuard {
  PixelFormatGuard(SDL_PixelFormat *format) : m_Format(format) {}
  PixelFormatGuard(SDL_PixelFormatEnum format_enum)
      : m_Format(AllocateFormat(format_enum)) {}
  PixelFormatGuard(uint32_t format_enum)
      : m_Format(AllocateFormat(format_enum)) {}

  ~PixelFormatGuard() {
    if (m_Format) {
      SDL_FreeFormat(m_Format);
    }
  }

public:
  SDL_PixelFormat *GetFormat() { return m_Format; }

private:
  SDL_PixelFormat *AllocateFormat(uint32_t format_enum) {
    SDL_PixelFormat *p_format = SDL_AllocFormat(format_enum);
    if (p_format == nullptr) {
      STELLAR_CORE_ERROR("PixelFormatGuard::PixelFormatGuard, Failed to allocate format, SDL Error: {0}, Failed at: {1}:{2}",  SDL_GetError(), STELLAR_FILENAME, STELLAR_LINE);
    }
    return p_format;
  }

private:
  SDL_PixelFormat *m_Format;
};

struct TextureDeleter {
  void operator()(SDL_Texture *texture) {
    if(texture != nullptr){
      SDL_DestroyTexture(texture);
      texture = nullptr;
    }
  }
};

struct SDL_Texture;

template<typename ... _Args>
using texture_is_constructible = typename std::is_constructible<std::shared_ptr<SDL_Texture>, _Args...>;

template<typename ... _Args>
inline constexpr bool texture_is_constructible_v = texture_is_constructible<_Args ...>::value;

template<typename... _Args>
using enable_if_texture_constructible_t = typename std::enable_if<!texture_is_constructible_v<_Args ...>>::type;

class Texture : public SourceDestRect<Texture> {
private:
public:
  Texture() noexcept;

  template<class Deleter = TextureDeleter,class = enable_if_texture_constructible_t<Deleter>>
  Texture(const Base::Ref<Renderer> renderer, const std::string &texture_path, Deleter deleter = TextureDeleter()){
    LoadTexture(renderer,texture_path,deleter);
  }

  ~Texture() noexcept;
  
  Texture(Texture &&other) noexcept {
    this->m_Texture = std::move(other.m_Texture);
    other.m_Texture = nullptr;
    this->m_src = std::move(other.m_src);
    this->m_dst = std::move(other.m_dst);
  }

  Texture(const Texture &other) {
    this->m_Texture = other.m_Texture;
    this->m_src = other.m_src;
    this->m_dst = other.m_dst;
  }

  template <typename Deleter = TextureDeleter,class = enable_if_texture_constructible_t<Deleter>>
  Base::Ref<SDL_Texture> LoadTexture(const Base::Ref<Renderer> renderer, const std::string &path, Deleter deleter = TextureDeleter()){
    return LoadTexture(*renderer,path,deleter);
  }

  template <typename Deleter = TextureDeleter,class = enable_if_texture_constructible_t<Deleter>>
  Base::Ref<SDL_Texture> LoadTexture(Renderer& renderer, const std::string &path, Deleter deleter = TextureDeleter()){
    Reset();

    m_Texture = std::move(Base::Ref<SDL_Texture>(IMG_LoadTexture(renderer,path.c_str()),deleter));
    if(m_Texture == nullptr){
      STELLAR_CORE_ERROR("Texture::LoadTexture(Renderer& renderer,const std::string &path : {0}), Failed to load texture, Failed at {1}:{2}",path,STELLAR_FILENAME,STELLAR_LINE);
      return nullptr;
    }

    return m_Texture;
  }
  
  [[nodiscard]] static Base::Ref<SDL_Texture> CreateTextureFromSurface(const Base::Ref<Renderer> renderer, SDL_Surface *surface);
  [[nodiscard]] static Base::Ref<SDL_Texture> CreateTextureFromSurface(Renderer& renderer, SDL_Surface *surface);

  [[nodiscard]] static Base::Ref<SDL_Texture> CreateTexture(const Base::Ref<Renderer> renderer, uint32_t format, int access, int w, int h);
  [[nodiscard]] static Base::Ref<SDL_Texture> CreateTexture(const Renderer& renderer, uint32_t format, int access, int w, int h);

  void ShareSDLTexture(const Texture &texture);
  void ShareSDLTexture(const Base::Ref<SDL_Texture> texture);
  void Reset();
  
  /**
   * @return Returns the number of different shared_ptr instances (this included) managing inner SDL_Texture pointer
  */
  long TextureUseCount() { return m_Texture.use_count(); }

  void UpdateTexturePixels(const SDL_Rect *rect, const void *pixels, int pitch);

  static void SetPixelAt(uint8_t *pixels, uint32_t texture_width,const Vec2 &point, Color color);
  static Color GetPixelColorAt(uint8_t *pixels, uint32_t texture_width, const Vec2 &point);
  
  [[nodiscard]] SDL_Texture *GetTexture() const { return m_Texture.get(); }
  [[nodiscard]] SDL_Texture *GetTexture() { return m_Texture.get(); }

  bool PointIsOnTexture(const Vec2 &point) const;

  static bool isColliding(const Texture &lhs, const Texture &rhs) {
    if (lhs.BottomRight().y <= rhs.TopLeft().y) {
      return false;
    }

    if (lhs.TopLeft().y >= rhs.BottomLeft().y) {
      return false;
    }

    if (lhs.TopRight().x <= rhs.TopLeft().x) {
      return false;
    }

    if (lhs.TopLeft().x >= rhs.TopRight().x) {
      return false;
    }
    return true;
  }

public:
  SDL_Texture *operator*() { return (m_Texture.get()); }

  SDL_Texture *operator*() const { return (m_Texture.get()); }

  Texture &operator=(const Texture &other) {
    if (this == &other) {
      return (*this);
    }
    this->m_Texture = other.m_Texture;

    this->m_src = other.m_src;
    this->m_dst = other.m_dst;
    return *this;
  }

  Texture &operator=(Base::Ref<SDL_Texture> texture) {
    if (m_Texture != texture) {
      Reset();
      m_Texture = texture;
    }
    return (*this);
  }

  Texture &operator=(Texture &&other) noexcept {
    if (this == &other) {
      return (*this);
    }
    this->m_dst = std::move(other.m_dst);
    this->m_src = std::move(other.m_src);
    this->m_Texture = std::move(other.m_Texture);

    return *this;
  }

  explicit operator bool() const noexcept { return (m_Texture != nullptr); }

  operator SDL_Texture*() const noexcept{
    return m_Texture.get();
  }
  
private:
  Base::Ref<SDL_Texture> m_Texture;
};

#endif //! __TEXTURE_HPP__