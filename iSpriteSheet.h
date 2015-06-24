#ifndef ISPRITESHEET_H_INCLUDED
#define ISPRITESHEET_H_INCLUDED

#include "spriteSheet.h"
#include "spriteCoords.h"
#include <map>
#include <vector>
#include <fstream>

class InanimateSpriteSheet: public SpriteSheet{
    public:
        map<int,SpriteCoords > states;
        bool loadSpriteMap(char* filename,int TAG,int TAG_TYPE);
        InanimateSpriteSheet(){};
};


#endif // ISPRITESHEET_H_INCLUDED
