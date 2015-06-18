#ifndef ASPRITESHEET_H_INCLUDED
#define ASPRITESHEET_H_INCLUDED

#include "spriteSheet.h"
#include "spriteCoords.h"
#include <map>
#include <list>
#include <vector>
#include <fstream>

class AnimateSpriteSheet: public SpriteSheet{
    public:
        map<int,list<SpriteCoords> > states;
        bool loadSpriteMap(char*,int TAG,int TAG_TYPE);
        list<SpriteCoords>::iterator currentAnim;


        AnimateSpriteSheet(){};
};

#endif // ASPRITESHEET_H_INCLUDED
