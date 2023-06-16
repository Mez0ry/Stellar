cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include(FindPackageHandleStandardArgs)

project(Stellar LANGUAGES CXX VERSION 0.18.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

find_package(spdlog REQUIRED)

include_directories(Stellar ${CMAKE_CURRENT_SOURCE_DIR}/Stellar)
include_directories(Stellar ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SPDLOG_INCLUDE_DIRS})

if(SDL2_FOUND)
	message("SDL2 found")
endif()

if(SDL2_IMAGE_FOUND)
	message("SDL2_image found")
endif()

if(SDL2_TTF_FOUND)
	message("SDL2_ttf found")
endif()

if(SDL2_MIXER_FOUND)
	message("SDL2_mixer found")
endif()

if(spdlog_FOUND)
	message("sdplog found")
endif()
 
add_library(Stellar
Stellar/Rect.hpp
Stellar/ObjectSize.hpp
Stellar/init_library.hpp
Stellar/Color.hpp
Stellar/Base.hpp

Stellar/EventHandler.hpp
Stellar/EventHandler.cpp

Stellar/MouseInput.hpp

Stellar/WindowInput.hpp
Stellar/Window.hpp
Stellar/Window.cpp

Stellar/Text.hpp
Stellar/Text.cpp
	
Stellar/Texture.hpp
Stellar/Texture.cpp

Stellar/Surface.hpp
Stellar/Surface.cpp
	
Stellar/Renderer.hpp
Stellar/Renderer.cpp

Stellar/Logger.hpp
Stellar/Logger.cpp
	
	
Stellar/Vector.hpp
Stellar/TextureGuard.hpp
Stellar/ServiceLocator.hpp
Stellar/KeyboardInput.hpp
Stellar/SourceDestRect.hpp
)

target_include_directories(Stellar PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SPDLOG_LIBRARIES})

target_link_libraries(Stellar SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer spdlog fmt)