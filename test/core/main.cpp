#include <iostream>
#include <SDL.h>
#include "EventManager.hpp"

// todo
bool gameRunning = true;
// Very precious
Uint32 USER_EVENT = SDL_RegisterEvents(1);

// EVENT BUS SYSTEM INITIALIZATION

EventManager EventBusMain;  // MAIN EVENT BUS

// COMPARTMENT INITIALIZATION FROM FIRST TO LAST
MainCompartment eventhandler_main(&EventBusMain); // main.cpp initialization
GameCompartment eventhandler_game(&EventBusMain);
MapCompartment eventhandler_map(&EventBusMain);
RenderCompartment eventhandler_render(&EventBusMain);
ConsoleCompartment eventhandler_console(&EventBusMain); // console.cpp initialization
// END COMPARTMENT DECLARATION

void MainCompartment::OnEventReceived(SDL_Event IncomingEvent){
	switch(IncomingEvent.type){
		case SDL_QUIT :
			gameRunning = false;
			break;
		
		default : // User event handling
		if(IncomingEvent.type == USER_EVENT){
			
			switch(IncomingEvent.user.code){
				case CONSOLE_TEST_OUTPUT :
				// std::cout<<"Received Console successfully!"<<std::endl;
				break;


				default:
				break;
			}
		}
		break;
	}
}

int main(int argc, char* argv[]) {

// Initialization of SDL

	std::cout<<"konzola"<<std::endl;
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		system("pause");
		// End the program
		return 1;
	}

// Framerate variables

	int FPS = 60; // Target frames per second
	int FrameDelay = 1000 / FPS; // Max amount of miliseconds between frames

	Uint32 FrameStart; // Get time at the beginning of a frame
	int FrameTime; // Calculate amount of time a frame lasted


	SDL_Event MainEvent;
	CREATEPUSH_USER(&MainEvent, INITIALIZE, &eventhandler_main, NULL, NULL); // initialization event

// Main game loop

	while (gameRunning == true) {
		FrameStart = SDL_GetTicks();
		// Handling of SDL events, mainly Input
		while(SDL_PollEvent(&MainEvent) != 0) {
			// Sends event into the Eventbus (EventManager)
			eventhandler_main.SendEvent(MainEvent);
		}

		CREATEPUSH_USER(&MainEvent, UPDATE, &eventhandler_main, NULL, NULL); //	update event

		// Push all
		EventBusMain.PushToCompartments();

		FrameTime = SDL_GetTicks() - FrameStart;

		// Check if frame needs to delay to match 60FPS or 16.67ms

		if (FrameDelay > FrameTime) {
			SDL_Delay(FrameDelay - FrameTime);
		}
		// std::cout<<SDL_GetTicks() - FrameStart<<std::endl; Milisecond outputter
	}



	SDL_Quit();	

	return 0;
}
