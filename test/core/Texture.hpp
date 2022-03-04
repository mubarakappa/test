#ifndef TEXTURE_GUARD
#define TEXTURE_GUARD

#include <SDL.h>
#include <iostream>

float TextureSizeModifier = 3.0;
int TILE_SIZE = 20 * TextureSizeModifier;
int OffsentCenterTile = (TILE_SIZE / 2);


extern SDL_Renderer* renderer;

class Texture {
    public:

    // Constructor
    Texture(){
        // Initialize
        InputTexture = NULL;
        width = 0;
        height = 0;
    }

    // Deconstructor
    ~Texture(){
        freeTexture();
    }

    // Returns width
    int GetWidth(){
        return width;
    }

    // Returns height
    int GetHeight(){
        return height;
    }
                                                                                // cyan
    // Load texture from file, bool if chromakey is needed (default chromakey: 0,255,255)
    bool LoadFromFile(std::string path, bool Chromakey){
        freeTexture();

        SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
        if(Chromakey){
            SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        }
        if( loadedSurface == NULL )
        {
            return false;
        }
        else
        {
        //Create texture from surface pixels
        InputTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
        if( InputTexture == NULL )
        {
            return false;
        }
        else{
            SDL_QueryTexture(InputTexture, NULL, NULL, &width, &height);
            return true;
        }
    }
    }

    // Render texture to global render
    void renderTexture(int X, int Y){
        // Useful for centering objects to the center of tile
        int offsetX = ((GetWidth() - 20) / 2) * TextureSizeModifier;
        int offsetY = ((GetHeight() - 20) / 2) * TextureSizeModifier;
        SDL_Rect renderRect = {X - offsetX, Y - offsetY, width * TextureSizeModifier, height * TextureSizeModifier};
        SDL_RenderCopy(renderer, InputTexture, NULL, &renderRect);
    }

    // Frees the texture
    void freeTexture(){
        //Free texture if it exists
        if( InputTexture != NULL )
        {
            SDL_DestroyTexture(InputTexture);
            InputTexture = NULL;
            width = 0;
            height = 0;
        }
    }

    private:
    SDL_Texture* InputTexture;

    int width;
    int height;


};



#endif