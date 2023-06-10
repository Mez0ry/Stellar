#ifndef __WINDOW_INFO_HPP__
#define __WINDOW_INFO_HPP__
#include "SDL2/SDL.h"
#include <bitset>

class WindowInput{
 public:
 WindowInput() {
    
 }

 ~WindowInput() = default;

 void SetStatus(SDL_WindowEventID event_id, bool status){
    m_EventsSet[event_id] = status;
 }
 
 bool OnEvent(SDL_WindowEventID event_id) const{
    return m_EventsSet[event_id];
 }
 
 void Reset(){
    m_EventsSet.reset();
 }

 std::bitset<255UL>::reference operator[](SDL_WindowEventID key){
    return m_EventsSet[key];
 }
 private:
  std::bitset<255> m_EventsSet;
};
#endif //!__WINDOW_INFO_HPP__