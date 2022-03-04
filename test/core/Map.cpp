#include <SDL.h>
#include <iostream>
#include "EventManager.hpp"

#define Grass "./img/grass.bmp"
#define Snow "./img/snow.bmp"

#define Fox "./img/char/fox.bmp"

// Define map size 200x200 tiles
int Map[200][200];
// Define characters
int CharPosMap[200][200] = {0};

void InitializeMap(){
    // hardcoded player spawn at top left
    for(int i = 0; i < 200; i++){
        for(int j = 0; j < 200; j++){
            if(i % 2 == 0){
                if(j % 2 == 0){
                    Map[i][j] = 0;
                }
                else{
                    Map[i][j] = 1;
                }
            }
            else{
                if(j % 2 == 0){
                    Map[i][j] = 1;
                }
                else{
                    Map[i][j] = 0;
                }
            }
        }
    }
}




void MapCompartment::OnEventReceived(SDL_Event IncomingEvent){
    switch(IncomingEvent.type){
        case SDL_QUIT :
        // idk save map
        break;

        default :
        if(IncomingEvent.type == USER_EVENT){
            switch(IncomingEvent.user.code){
                case INITIALIZE :
                InitializeMap();
                case UPDATE :
                // update character movement or smth
                

                default :
                break;
            }
        }
        break;
    }
}
