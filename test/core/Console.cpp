#include <iostream>
#include <SDL.h>
#include "EventManager.hpp"

// Debugging user events
void ConsoleCompartment::OnEventReceived(SDL_Event IncomingEvent){
    switch(IncomingEvent.type){
        case SDL_QUIT :
        std::cout<<"Quit requested"<<std::endl;
        break;

        default :
        if(IncomingEvent.type == USER_EVENT){
            switch(IncomingEvent.user.code){
                case INITIALIZE :
                std::cout<<"Initialization event"<<std::endl;
                case UPDATE :
                // std::cout<<"Update event"<<std::endl;
                

                default :
                break;
            }
        }
        break;
    }
}