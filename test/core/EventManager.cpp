#include <SDL.h>
#include "EventManager.hpp"

void CREATEPUSH_USER(SDL_Event* Event, Sint32 Code, EventHandler* Compartment, void* info1, void* info2){
  Event->type = USER_EVENT;
  Event->user.code = Code;
  Event->user.data1 = info1;
  Event->user.data2 = info2; // When the time comes implement data correctly

  Compartment->SendEvent(*Event);
}
