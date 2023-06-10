#ifndef __SDL_LIBRARIES_HPP__
#define __SDL_LIBRARIES_HPP__
#include "Logger.hpp"
#include <functional>
#include <type_traits>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <optional>

struct SDL_Image{
    std::function<int(uint32_t flags)> m_init = &IMG_Init;
    std::function<void()> m_deinit = &IMG_Quit;

    bool Init(uint32_t flags) {
        if(((m_init(flags)) & flags) != flags){
            return false;
        }
        
        return true;
    }
};

struct SDL{
    std::function<int(uint32_t flags)> m_init = &SDL_Init;
    std::function<void()> m_deinit = &SDL_Quit;

    bool Init(uint32_t flags) {
        if(m_init(flags) == 0){
            return true;
        }
        
        return false;
    }
};

struct SDL_TTF{
    std::function<int(void)> m_init = &TTF_Init; 
    std::function<void()> m_deinit = &TTF_Quit;

    bool Init(){
        if(m_init() == 0){
            return true;
        }
        return false;
    }
};

template<typename T, typename dummy = T>
struct is_sdl_library : std::false_type{

};

template < typename T >
struct is_sdl_library< T,typename std::enable_if_t<(std::is_same<T, SDL>::value || std::is_same<T, SDL_Image>::value || std::is_same<T,SDL_TTF>::value), T >> : std::true_type
{
    
};

template <typename T>
class init_library{
private:
public:
    init_library(std::optional<uint32_t> flags = std::nullopt){
        if(!Logger::IsCreated()){
            Logger::OnCreate();
        }
        
        STELLAR_ASSERT(is_sdl_library<T>::value,"template argument T is not and SDL library, it has type {0} ", typeid(T).name());

        char library_name[100];
        std::memset(&library_name,'\0',sizeof(char) * 100);
        std::memcpy(&library_name,&typeid(T).name()[1],strlen(typeid(T).name()) - 1);

        if constexpr(std::is_invocable_v<decltype(&T::Init),T&,uint32_t>){
            if(T().Init(flags.value()) ){
                STELLAR_CORE_INFO("{0} library successfully initialized",library_name);
            }else{
                STELLAR_CORE_ERROR("Failed to initialize {0} library, {0} Error: {1} ",library_name,GetError<T>());
            }

        }else{
            if(T().Init()){
                STELLAR_CORE_INFO("{0} library successfully initialized",library_name);
            }else{
                STELLAR_CORE_ERROR("Failed to initialize {0} library, {0} Error: {1} ",library_name,GetError<T>());
            }
        }
    }
    
    ~init_library(){
        char library_name[100];
        std::memset(&library_name,'\0',sizeof(char) * 100);
        std::memcpy(&library_name,&typeid(T).name()[1],strlen(typeid(T).name()) - 1);

        T().m_deinit();
        
        STELLAR_CORE_INFO("{0} library successfully deinitialized",library_name);
    }
    
    init_library(const init_library&) = delete;
    init_library(init_library&&) = delete;
private:

 template <typename _Type>
 auto GetError() const{
    if constexpr(std::is_same_v<_Type,SDL>){
        return SDL_GetError();
    }else if constexpr(std::is_same_v<_Type,SDL_Image>){
        return IMG_GetError();
    }else if constexpr(std::is_same_v<_Type,SDL_TTF>){
        return TTF_GetError();
    }
 }
};

#endif //!__SDL_LIBRARIES_HPP__