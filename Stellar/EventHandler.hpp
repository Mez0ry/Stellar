#ifndef __EVENT_HANDLER_HPP__
#define __EVENT_HANDLER_HPP__
#include "SDL2/SDL.h"
#include "KeyboardInput.hpp"
#include "WindowInput.hpp"
#include "MouseInput.hpp"

class EventHandler {
public:
  EventHandler() : m_IsQuit(false), m_MouseInMotion(false) {}
  ~EventHandler() = default;
  
  EventHandler(const EventHandler &) = delete;
  EventHandler(EventHandler &&) = delete;
  EventHandler &operator=(const EventHandler &) = delete;
  EventHandler &operator=(EventHandler &&) = delete;
  
  bool IsQuit() const {return m_IsQuit;}
  bool OnMouseMotion() const {return m_MouseInMotion;}
  void PollEvents();
  
  KeyboardInput& GetKeyboardInput() {return m_KeyboardInput;}
  WindowInput& GetWindowInput() {return m_WindowInput;}
  MouseInput& GetMouseInput() {return m_MouseInput;}

private:
  SDL_Event m_Event;
  KeyboardInput m_KeyboardInput;
  WindowInput m_WindowInput;
  MouseInput m_MouseInput;
  bool m_IsQuit;
  bool m_MouseInMotion;
};
#endif //!__EVENT_HANDLER_HPP__