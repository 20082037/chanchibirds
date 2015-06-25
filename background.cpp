#include "background.h"

Background::Background(GLfloat xi,GLfloat yi,GLfloat zi,InanimateSpriteSheet* ssheet,int wWidth,int ta){
    tag = ta;
    x = xi;
    y = yi;
    z = zi;
    sprites = ssheet;
    state = BACKGROUND_NORMAL;
    height =ssheet->states[BACKGROUND_NORMAL].c2.second-ssheet->states[BACKGROUND_NORMAL].c1.second;
    width =ssheet->states[BACKGROUND_NORMAL].c2.first-ssheet->states[BACKGROUND_NORMAL].c1.first;
    scale = 1;
    height = scale*wWidth*height / width;
    width = scale*wWidth;

//    body->SetUserData(this);
}

void Background::draw(){
    glPushMatrix();
    glTranslatef(x,y,z);
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
