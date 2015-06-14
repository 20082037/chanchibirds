#ifndef ASPRITESHEET_H_INCLUDED
#define ASPRITESHEET_H_INCLUDED

#include "spriteSheet.h"

#include <map>
#include <list>
class AnimateSpriteSheet: public SpriteSheet{
    public:
        map<int,list<SpriteCoords> > states;
        bool loadSpriteMap(ifstream &file,int TAG,int TAG_TYPE);
};

#endif // ASPRITESHEET_H_INCLUDED
