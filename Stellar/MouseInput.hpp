#ifndef __MOUSE_INPUT_HPP__
#define __MOUSE_INPUT_HPP__
#include <bitset>
#include "SDL2/SDL_mouse.h"
#include "Vector.hpp"
#include <unordered_map>

class MouseInput{
 public:
 MouseInput() = default;
 ~MouseInput() = default;

 bool IsPressed(int32_t button){
    return m_Button[button];
 }

 bool IsReleased(int32_t button){
   return !(m_Button[button]);
 }
 
 Vec2 GetMousePosition(){
   Vec2 pos;
   SDL_GetMouseState(&pos.x,&pos.y);
   return pos;
 }
 
 std::bitset<10UL>::reference operator[](int32_t button){
    return m_Button[button];
 }
 
private:
 std::bitset<10> m_Button;
};
#endif //! __MOUSE_INPUT_HPP__