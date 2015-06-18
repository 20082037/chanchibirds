#include "ground.h"

Ground::Ground(float xi,float yi,float zi,InanimateSpriteSheet* ssheet,b2World* world){
    this->x=xi;
    this->y=yi;
    this->z=zi;
    this->sprites = ssheet;
    this->width = ssheet->states[0].c2.second - ssheet->states[0].c1.second;
    this->height = ssheet->states[0].c2.first-ssheet->states[0].c1.first;

    this->defBody.type = b2_staticBody;
    this->defBody.position.Set(this->x,this->yi);
    this->body = world -> CreateBody(& this->defBody);
    this->shape.SetAsBox(this->width/2 , this->height/2);
    this->body->CreateFixture(& this->pShape,0.0f);

    this->state=0;
}
