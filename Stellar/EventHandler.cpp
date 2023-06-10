#include "EventHandler.hpp"

void EventHandler::PollEvents(){
    m_WindowInput.Reset();
    
    while(SDL_PollEvent(&m_Event)){
    switch(m_Event.type){
      case SDL_QUIT:{
        m_IsQuit = true;
        break;
      }
      case SDL_KEYDOWN:{
        m_KeyboardInput[m_Event.key.keysym.sym] = true;
        break;
      }
      
      case SDL_KEYUP:{
        m_KeyboardInput[m_Event.key.keysym.sym] = false;
        break;
      }

      case SDL_WINDOWEVENT:{
        m_WindowInput.SetStatus(static_cast<SDL_WindowEventID>(m_Event.window.event),true);
        break;
      }
    }
    SDL_Delay(3);
  }
}