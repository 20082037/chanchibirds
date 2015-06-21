#include "ground.h"

Ground::Ground(float xi,float yi,float zi,InanimateSpriteSheet* ssheet,b2World* world){
    z = zi;
    sprites = ssheet;
    state=0;
    height = ssheet->states[0].c2.second - ssheet->states[0].c1.second;
    width = ssheet->states[0].c2.first - ssheet->states[0].c1.first;

    defBody.type = b2_staticBody;
    defBody.position.Set(xi,yi);
    body = world -> CreateBody(&defBody);
    shape.SetAsBox(width/2 , height/2);
    body->CreateFixture(&shape,0.0f);
}

void Ground::draw(){
    glPushMatrix();
    // glTranslatef(this->x,this->y,this->z);
    glTranslatef(body->GetPosition().x,body->GetPosition().y,z);
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
