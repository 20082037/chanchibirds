#ifndef ISPRITESHEET_H_INCLUDED
#define ISPRITESHEET_H_INCLUDED

#include "spriteSheet.h"
#include <map>
#include <vector>
#include <fstream>

class InanimateSpriteSheet: public SpriteSheet{
    public:
        map<int,SpriteCoords > states;
        bool loadSpriteMap(ifstream& file,int TAG,int TAG_TYPE);
        InanimateSpriteSheet();
};


#endif // ISPRITESHEET_H_INCLUDED
