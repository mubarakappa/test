#include <iostream>
#include <SDL.h>
#include "Render.hpp"
#include "EventManager.hpp"
#include "Texture.hpp"
#include "Map.hpp"
#include "Game.hpp"

#define LEVEL_WIDTH 12000
#define LEVEL_HEIGHT 12000

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define Grass "./img/grass.bmp"
#define Snow "./img/snow.bmp"

#define Fox "./img/char/fox.bmp"

  

  SDL_Window* window = NULL; // Game Window
  SDL_Renderer* renderer = NULL; // Game Renderer
  Texture GrassText = Texture();
  Texture SnowText = Texture();
  Texture FoxText = Texture();

  SDL_Rect TilePos; // Texture rectangle
  SDL_Rect Camera; // Camera position relative to center of fox

  extern int Map[200][200]; // Referencing map in cpp file
  extern int CharPosMap[200][200];

  extern float TextureSizeModifier;
  extern int TILE_SIZE;
  extern int OffsentCenterTile;

  extern Player FoxPlayer; // Points to player


// SDL_Texture* loadTexture( std::string path, bool colorkey )
// {
//     //The final texture
//     SDL_Texture* newTexture = NULL;

//     //Load image at specified path
//     SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
//     if(colorkey){
//     SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );
//     }
//     if( loadedSurface == NULL )
//     {
//         printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str());
//     }
//     else
//     {
//         //Create texture from surface pixels
//         newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
//         if( newTexture == NULL )
//         {
//             printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
//         }

//         //Get rid of old loaded surface
//         SDL_FreeSurface( loadedSurface );
//     }

//     return newTexture;
// }

// void TileToPixel(int* XTile, int* YTile){
//   // get data from pointer, probably could do it immediately but better be safe like this
//   int X = *XTile;
//   int Y = *YTile;
//   int PixelX = (X * TILE_SIZE) + OffsentCenterTile;
//   int PixelY = (Y * TILE_SIZE) + OffsentCenterTile;

//   // assign value to pointer tldr tile input center of tile pixel output
//   *XTile = PixelX;
//   *YTile = PixelY;
// }


// void FindFox(int* ReturnX, int* ReturnY){
//   //find coord of fox
//   int XFox, YFox;
//   for(int i = 0; i < 200; i++){
//     for(int j = 0; j < 200; j++){
//       if(CharPosMap[i][j] == 1){
//         XFox = j;
//         YFox = i;
//         goto end;
//       }
//     }
//   }
//   end:
//   // assign pointer value to fox coord
//   *ReturnX = XFox;
//   *ReturnY = YFox;
// }


void Create() {
    TilePos.x = 0;
    TilePos.y = 0;
    TilePos.w = TILE_SIZE;
    TilePos.h = TILE_SIZE;
  // Create window
  window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  // Error Catcher
  if ( !window ) {
    std::cout << "Error creating window: " << SDL_GetError()  << std::endl;
    system("pause");
    // End the program
    return;
  }
  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  // Error Catcher
  if (!renderer) {
        std::cout << "Error creating window: " << SDL_GetError()  << std::endl;
    system("pause");
    // End the program
    return;
  }
  // Initialize textures
  GrassText.LoadFromFile(Grass, false);
  SnowText.LoadFromFile(Snow, false);
  FoxText.LoadFromFile(Fox, true);

  // Find fox pixel coords
  // int XFox, YFox;
  // FindFox(&XFox, &YFox);
  // std::cout<<"Fox on tile: "<<XFox<<" "<<YFox<<std::endl;
  // // Find coordinate of tile on fox
  // TileToPixel(&XFox, &YFox);
  // std::cout<<"Fox on pixel: "<<XFox<<" "<<YFox<<std::endl;

  // int XFox, YFox;
  // FoxPlayer.GetTilePixelCoord(&XFox, &YFox);

  // // Setup camera on fox center (top left camera orig point)
  //   Camera.x = XFox - SCREEN_WIDTH / 2;
  //   Camera.y = YFox - SCREEN_HEIGHT / 2;
  // not really bitno but must be initializes
    Camera.w = 0;
    Camera.h = 0;
}

// Rendering map todo implement sizeable maps
void Update(){
  // Update camera
    int XFox, YFox;
    FoxPlayer.GetTilePixelCoord(&XFox, &YFox);
    Camera.x = XFox - SCREEN_WIDTH / 2;
    Camera.y = YFox - SCREEN_HEIGHT / 2;
  // Reset position with offset to camera
  TilePos.x = 0 - Camera.x; 
  TilePos.y = 0 - Camera.y;
  // Reset Render
  SDL_RenderClear(renderer);

  // Rendering whole map (inefficient)
  for(int i = 0; i < 200; i++){
    for(int j = 0; j < 200; j++){
      if(Map[i][j] == 0){
        GrassText.renderTexture(TilePos.x, TilePos.y);
      }
      else{
        SnowText.renderTexture(TilePos.x, TilePos.y);
      }
      TilePos.x = TilePos.x + TILE_SIZE;
    }
    TilePos.x = 0 - Camera.x;
    TilePos.y = TilePos.y + TILE_SIZE;
  }
  // Rendering characters
  TilePos.x = 0 - Camera.x; 
  TilePos.y = 0 - Camera.y;
  for(int i = 0; i < 200; i++){
    for(int j = 0; j < 200; j++){
      if(CharPosMap[i][j] == 1){
        FoxText.renderTexture(TilePos.x, TilePos.y);
      }
      TilePos.x = TilePos.x + TILE_SIZE;
    }
    TilePos.x = 0 - Camera.x; 
    TilePos.y = TilePos.y + TILE_SIZE;
  }
  SDL_RenderPresent(renderer);
}

void Clean(){

}


void RenderCompartment::OnEventReceived(SDL_Event IncomingEvent){
  switch(IncomingEvent.type){
    
    
    default :
    
    if(IncomingEvent.type == USER_EVENT){
      switch(IncomingEvent.user.code){

        case INITIALIZE : 
        Create();
        break;
        
        case UPDATE :
        Update();
        break;

        default :
        break;

      }
    }
  }
}
