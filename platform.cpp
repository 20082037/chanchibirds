#include "platform.h"

Platform::Platform(GLfloat xi,GLfloat yi,GLfloat zi,InanimateSpriteSheet* ssheet){//Provisional, se debería proveer direction y speed
    this->x=xi;
    this->y=yi;
    this->z=zi;
    this->sprites = ssheet;
    this->width=ssheet->states[PLATFORM_HEALTHY].c2.second-ssheet->states[PLATFORM_HEALTHY].c1.second;
    this->height=ssheet->states[PLATFORM_HEALTHY].c2.first-ssheet->states[PLATFORM_HEALTHY].c1.first;
    this->state=PLATFORM_HEALTHY;
}

void Platform::draw(){
    glPushMatrix();
    glTranslatef(this->x,this->y,this->z);
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
