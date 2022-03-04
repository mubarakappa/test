#include <SDL.h>
#include <iostream>
#include "EventManager.hpp"
#include "Game.hpp"

// Create Player object
Player FoxPlayer;

// Game handling

void CreateObjects(){
	
	// Putting player at 0X, 0Y, Type: player
	FoxPlayer.InitializeOnMap(0, 0, 1);


}

void PlayerMovement(SDL_Event KeyPress){
	switch(KeyPress.key.keysym.sym){
		case SDLK_LEFT :
		FoxPlayer.MoveX(-1);
		break;
		case SDLK_RIGHT :
		FoxPlayer.MoveX(1);
		break;
		case SDLK_UP :
		FoxPlayer.MoveY(-1);
		break;
		case SDLK_DOWN :
		FoxPlayer.MoveY(1);
		break;
	}
}

// Event handling

void GameCompartment::OnEventReceived(SDL_Event IncomingEvent){
	switch(IncomingEvent.type){
		case SDL_QUIT :
			break;
		case SDL_KEYDOWN :
			PlayerMovement(IncomingEvent);
		
		default : // User event handling
		if(IncomingEvent.type == USER_EVENT){
			
			switch(IncomingEvent.user.code){
				case INITIALIZE :
				CreateObjects();
				break;


				default:
				break;
			}
		}
		break;
	}
}



