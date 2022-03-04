#ifndef GAME_GUARD
#define GAME_GUARD

#include <SDL.h>
#include <stdlib.h>
#include <time.h>

extern int CharPosMap[200][200];
extern float TextureSizeModifier;
extern int TILE_SIZE; 
extern int OffsentCenterTile;

const int PLAYER = 1;
const int ENEMY = 2;
const int FRIEND = 3;
const int PREY = 4;
const int INTERACTABLE_OBJECT = 5;
const int UNINTERACTABLE_OBJECT = 6;


class Object {
    public:
    // Initialize object
    Object(){};

    ~Object(){}; // Kill it :(

    void InitializeOnMap(int Xpos, int Ypos, int TypeOfObject){
        // Put object onto map
        CharPosMap[Ypos][Xpos] = TypeOfObject;
        // Save tile location
        ObjectLocation[0] = Xpos;
        ObjectLocation[1] = Ypos;
        // Save pixel coords of said tile (center)
        PixelPosTile[0] = Xpos * TILE_SIZE + OffsentCenterTile;
        PixelPosTile[1] = Ypos * TILE_SIZE + OffsentCenterTile; 
        // Save object type
        ObjectType = TypeOfObject;       

    };

    virtual void MoveAI(){};
    
    virtual void MoveX(int Move){
            // Check Constraint
            if(ObjectLocation[0] + Move >= 0 && ObjectLocation[0] + Move < 200){
                // Destroy object at original position
                CharPosMap[ObjectLocation[1]][ObjectLocation[0]] = 0;
                // Update Object at new position
                CharPosMap[ObjectLocation[1]][ObjectLocation[0] + Move] = ObjectType;
                // Save new position of object
                UpdateTile(ObjectLocation[0] + Move, ObjectLocation[1]);
            }
    };

    virtual void MoveY(int Move){
            // Check Constraint
            if(ObjectLocation[1] + Move >= 0 && ObjectLocation[1] + Move < 200){
                // Destroy object at original position
                CharPosMap[ObjectLocation[1]][ObjectLocation[0]] = 0;
                // Update Object at new position
                CharPosMap[ObjectLocation[1] + Move][ObjectLocation[0]] = ObjectType;
                // Save new position of object
                UpdateTile(ObjectLocation[0], ObjectLocation[1] + Move);                                
            }
    };
    
    // Given two pointers, this function will insert tile position into two pointers because return doesn't like returning two pieces of data;
    void GetTile(int* XPos, int* YPos){
        *XPos = ObjectLocation[0];
        *YPos = ObjectLocation[1];
    };

    void GetTilePixelCoord(int* XPos, int* YPos){
        *XPos = PixelPosTile[0];
        *YPos = PixelPosTile[1];
    };

    void UpdateTile(int XPos, int YPos){
        ObjectLocation[0] = XPos;
        ObjectLocation[1] = YPos;
        UpdateTilePixelCoord(XPos, YPos);
    }

    void UpdateTilePixelCoord(int XPos, int YPos){
        PixelPosTile[0] = XPos * TILE_SIZE + OffsentCenterTile;
        PixelPosTile[1] = YPos * TILE_SIZE + OffsentCenterTile; 
    }

    private:
    int ObjectLocation[2]; // Array storing object X and Y pos on tile
    int PixelPosTile[2]; // Array storing object X and Y pixel position on map
    int ObjectType; // Int storing object type
};

class Player : public Object {
    public:

    Player() : Object() {};


};

class Bunny : public Object {
    public:

    Bunny() : Object() {};

    void MoveAi(){
        srand(time(0));
        rand()
    };
};


#endif