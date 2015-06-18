#include "ground.h"

Ground::Ground(float xi,float yi,float zi,InanimateSpriteSheet* ssheet,b2World* world){

    this->defBody.type = b2_staticBody;
    this->defBody.position.Set(xi,yi);
    this->body = world -> CreateBody(& this->defBody);
    this->shape.SetAsBox(this->width/2 , this->height/2);
    this->body->CreateFixture(& this->shape,0.0f);

    this->state=0;

    // this->x = &this->body->GetPosition().x;
    // this->y = &this->body->GetPosition().y;
    this->z = zi;
    this->sprites = ssheet;
    this->width = ssheet->states[0].c2.second - ssheet->states[0].c1.second;
    this->height = ssheet->states[0].c2.first-ssheet->states[0].c1.first;
}

void Ground::draw(){
    static int i=1;
    i++;
    if(i<14)
        cout<<"I'm Ground : pos: "<<this->body->GetPosition().x<<" "<<this->body->GetPosition().y<<endl;

    glPushMatrix();
    // glTranslatef(this->x,this->y,this->z);
    glTranslatef(this->body->GetPosition().x,this->body->GetPosition().y,this->z);
    glBindTexture(GL_TEXTURE_2D,sprites->texID);
    glBegin(GL_QUADS);
        glTexCoord2f(sprites->states[state].c1.first/sprites->imageWidth,sprites->states[state].c2.second/sprites->imageHeight);
        glVertex3f(-width/2,height/2,0);
        glTexCoord2f(sprites->states[state].c1.first/sprites->imageWidth,sprites->states[state].c1.second/sprites->imageHeight);
        glVertex3f(-width/2,-height/2,0);
        glTexCoord2f(sprites->states[state].c2.first/sprites->imageWidth,sprites->states[state].c1.second/sprites->imageHeight);
        glVertex3f(width/2,-height/2,0);
        glTexCoord2f(sprites->states[state].c2.first/sprites->imageWidth,sprites->states[state].c2.second/sprites->imageHeight);
        glVertex3f(width/2,height/2,0);
    glEnd();
    glPopMatrix();
}
