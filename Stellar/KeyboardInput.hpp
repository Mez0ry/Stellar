#ifndef __KEYBOARD_INPUT__HPP
#define __KEYBOARD_INPUT__HPP
#include <bitset>
#include "SDL2/SDL_keyboard.h"

class KeyboardInput{
 public:
 KeyboardInput() = default;
 ~KeyboardInput() = default;

 bool IsPressed(int32_t key){
    return m_Keys[key];
 }

 bool IsReleased(int32_t key){
   return !(m_Keys[key]);
 }

 size_t size() const {return m_Keys.size();}

 std::bitset<351UL>::reference operator[](int32_t key){
    if(static_cast<uint32_t>(key) > m_Keys.size()){
        key = KeycodeFixedLayout(key);
    }
    return m_Keys[key];
 }
 private:
 int32_t KeycodeFixedLayout(int32_t key_code) const{
    return (key_code - (SDLK_SCANCODE_MASK)) + 66;
 }
 
 private:
 std::bitset<351> m_Keys;
};
#endif //!__KEYBOARD_INPUT__HPP