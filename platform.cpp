#include "platform.h"

Platform::Platform(GLfloat xi,GLfloat yi,GLfloat zi,InanimateSpriteSheet* ssheet,b2World* world, int wWidth,int ta){//Provisional, se debería proveer direction y speed
    tag = ta;
    z=zi;
    sprites = ssheet;
    //width = 100.f;
    //height = 5.f;
    height=ssheet->states[PLATFORM_HEALTHY].c2.second-ssheet->states[PLATFORM_HEALTHY].c1.second;
    width=ssheet->states[PLATFORM_HEALTHY].c2.first-ssheet->states[PLATFORM_HEALTHY].c1.first;
    state=PLATFORM_HEALTHY;
    scale = 1/10.f;
    height = scale*wWidth*height / width;
    width = scale*wWidth;

    limy = -300.f - height/2;

    defBody.position.Set(xi,yi);
    defBody.type = b2_kinematicBody;
    defBody.linearVelocity.Set(0.f,-20.f);
    body = world->CreateBody(&defBody);
    body->SetUserData(this);

    shape.SetAsBox(width/2, height/2);

    fixture.shape = &shape;
    fixture.friction = 0.3f;
    fixture.filter.groupIndex = -8;
    fixture.restitution = 0.f;

    body->CreateFixture(&fixture);

    massDa.mass = 300.f;

    body->SetMassData(&massDa);

//    body->SetUserData(this);
}

void Platform::draw(){
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);


    if(body->GetPosition().y < limy){
        b2World* aux = body->GetWorld();

        defBody.position.Set(body->GetPosition().x,230.f);
        body = aux->CreateBody(&defBody);
        body->CreateFixture(&fixture);
        body->SetMassData(&massDa);

    }
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

    glDisable(GL_BLEND);
    glPopMatrix();
}
