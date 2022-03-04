#ifndef EVENT_GUARD
#define EVENT_GUARD

#include <SDL.h>
#include <queue>
#include <vector>
#include <iostream>
#include <functional>



//EVENT BUS
class EventManager {
  public:
    EventManager(){}; //Constructor
    ~EventManager(){}; //Deconstructor

    //Pushing event to bus ie. Input
    void PushToBus(SDL_Event event){
      Events.push(event);
      return;
    }

    //Pushing events to compartments ie. Output
    void PushToCompartments(){
      while(!Events.empty()){
        for (auto iter = Compartments.begin(); iter != Compartments.end(); iter++) {
          (*iter)(Events.front());
          }
        Events.pop();
        }
      return;
    }

    //Adds a compartment
    void AddCompartment(std::function<void (SDL_Event)> EventCompartment){
    Compartments.push_back(EventCompartment);
    return;
    }

  private:
    std::queue<SDL_Event> Events; // The event bus containing events to push to other compartments
    std::vector<std::function<void (SDL_Event)>> Compartments; // The addresses of event handlers that will handle events getting received in a compartment
};

extern EventManager EventBusMain; // Pointer to EventBusMain in main.cpp

//COMPARTMENT TEMPLATE
class EventHandler {
  public:
  // Constructor automatically adds compartment to compartment list
  EventHandler(EventManager *InputtedEventbus){
    this->EventBus = InputtedEventbus; //Tells the eventbus pointer in the class is equal to the inputted eventbus from the constructor
    this->EventBus->AddCompartment(this->getNotifyFunc());
  }
  // Sends event
  void SendEvent(SDL_Event Event){
    EventBus->PushToBus(Event);
  }
  protected:
    EventManager* EventBus;

      // Points to receiver function
    std::function<void (SDL_Event)> getNotifyFunc()
  {
    auto messageListener = [=](SDL_Event Event) -> void {
        this->OnEventReceived(Event);
    };
    return messageListener;
  }
  // Receiver Function
  virtual void OnEventReceived(SDL_Event IncomingEvent){
      std::cout << "Siopao! Siopao! Siopao! (Someone forgot to implement OnEventReceived().)" << std::endl;
  }
};

//COMPARTMENTS
class MainCompartment : public EventHandler 
{
	public:
	MainCompartment(EventManager* EventBus) : EventHandler(EventBus) {}
	private:
	void OnEventReceived(SDL_Event IncomingEvent);
};

class RenderCompartment : public EventHandler 
{
	public:
	RenderCompartment(EventManager* EventBus) : EventHandler(EventBus) {}
	private:
	void OnEventReceived(SDL_Event IncomingEvent);
};

class ConsoleCompartment : public EventHandler 
{
	public:
	ConsoleCompartment(EventManager* EventBus) : EventHandler(EventBus) {}
	private:
	void OnEventReceived(SDL_Event IncomingEvent);
};

class GameCompartment : public EventHandler 
{
	public:
	GameCompartment(EventManager* EventBus) : EventHandler(EventBus) {}
	private:
	void OnEventReceived(SDL_Event IncomingEvent);
};

class MapCompartment : public EventHandler 
{
	public:
	MapCompartment(EventManager* EventBus) : EventHandler(EventBus) {}
	private:
	void OnEventReceived(SDL_Event IncomingEvent);
};


// COMPARTMENT EXTERNS

  extern MainCompartment eventhandler_main; // main.cpp compartment
  extern RenderCompartment eventhandler_render; // render.cpp compartment
  extern ConsoleCompartment eventhandler_console; // console.cpp compartment
  extern MapCompartment eventhandler_map;
  extern GameCompartment eventhandler_game; // game.cpp compartment




// USER EVENTS
extern Uint32 USER_EVENT;

const Sint32 CONSOLE_TEST_OUTPUT = 1;
const Sint32 INITIALIZE = 2;
const Sint32 UPDATE = 3;


void CREATEPUSH_USER(SDL_Event* Event, Sint32 Code, EventHandler* Compartment, void* info1, void* info2);


#endif
