#include "platform.h"

Platform::Platform(GLfloat xi,GLfloat yi,GLfloat zi,InanimateSpriteSheet* ssheet,b2World* world){//Provisional, se debería proveer direction y speed
    z=zi;
    sprites = ssheet;
    width = 100.f;
    height = 5.f;
    //this->width=ssheet->states[PLATFORM_HEALTHY].c2.second-ssheet->states[PLATFORM_HEALTHY].c1.second;
    //this->height=ssheet->states[PLATFORM_HEALTHY].c2.first-ssheet->states[PLATFORM_HEALTHY].c1.first;
    state=PLATFORM_HEALTHY;


    defBody.position.Set(xi,yi);
    defBody.type = b2_kinematicBody;
    defBody.linearVelocity.Set(0.f,20.f);
    body = world->CreateBody(&defBody);

    shape.SetAsBox(width/2, height/2);

    fixture.shape = &shape;
    fixture.friction = 0.3f;
    fixture.filter.groupIndex = -8;
    fixture.restitution = 0.f;

    body->CreateFixture(&fixture);

    massDa.mass = 300.f;

    body->SetMassData(&massDa);

}

void Platform::draw(){
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
