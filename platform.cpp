#include "platform.h"

Platform::Platform(GLfloat xi,GLfloat yi,GLfloat zi,InanimateSpriteSheet* ssheet,b2World* world){//Provisional, se debería proveer direction y speed
    this->x=xi;
    this->y=yi;
    this->z=zi;
    this->sprites = ssheet;
    this->width = 100.f;
    this->height = 10.f;
    //this->width=ssheet->states[PLATFORM_HEALTHY].c2.second-ssheet->states[PLATFORM_HEALTHY].c1.second;
    //this->height=ssheet->states[PLATFORM_HEALTHY].c2.first-ssheet->states[PLATFORM_HEALTHY].c1.first;
    this->state=PLATFORM_HEALTHY;

    this->defBody.position.Set(this->x,this->y);
    this->defBody.type = b2_kinematicBody;
    this->defBody.linearVelocity.Set(0.f,20.f);
    this->body = world->CreateBody(& this->defBody);

    this->shape.SetAsBox(this->width/2, this->height/2);

    this->fixture.shape = & this->shape;
    this->fixture.friction = 0.3f;
    this->fixture.filter.groupIndex = 8;
    this->fixture.restitution = 0.f;

    this->body->createFixture(&this->fixture);

    this->mass.mass = 300.f;

    this->body->SetMassData(&this->mass);
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
