#include "pig.h"

Pig::Pig(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet* ssheet, b2World* world){//Provisional, se debería proveer direction y speed
    z=zi;
    sprites = ssheet;
    width=ssheet->states[PIG_HEALTHY].begin()->c2.second - ssheet->states[PIG_HEALTHY].begin()->c1.second;
    height=ssheet->states[PIG_HEALTHY].begin()->c2.first - ssheet->states[PIG_HEALTHY].begin()->c1.first;
//    cout<<"PIG: "<<width<<" "<<height<<endl;

    state=PIG_HEALTHY;
    currentAnim=sprites->states[state].begin();


    defBody.type = b2_dynamicBody;
    defBody.position.Set(xi,yi);
    body = world -> CreateBody(&defBody);

    shape.m_p.Set(0.f,0.f);
    shape.m_radius=height/2;
    fixture.shape =  &shape;
    fixture.restitution = 0.3f;
    fixture.friction = 0.3f;
    fixture.density = 0.3f;

    body->CreateFixture(&fixture);

//    massDa.mass=300.f;
//    body->SetMassData(&massDa);
    shape.ComputeMass(&massDa, fixture.density);
    
//    cout<<"PIG MASS: "<<body->GetMass()<<endl;

    // this->x= & this->body->GetPosition().x;
    // this->y= & this->body->GetPosition().y;
}

void Pig::animate(){
    if(currentAnim==--sprites->states[state].end()){
        currentAnim=sprites->states[state].begin();
    }else{
        currentAnim++;
    }
}

void Pig::draw(){
    glPushMatrix();
    glTranslatef(body->GetPosition().x,body->GetPosition().y,z);
    //cout<<"Chancho Posicion: "<<body->GetPosition().x<<" "<<body->GetPosition().y<<endl;
    // glTranslatef(this->x,this->y,this->z);
    glBindTexture(GL_TEXTURE_2D,sprites->texID);
    glBegin(GL_QUADS);
        glTexCoord2f(currentAnim->c1.first / sprites->imageWidth,currentAnim->c2.second / sprites->imageHeight);
        glVertex3f(-width/2,height/2,0);
        glTexCoord2f(currentAnim->c1.first / sprites->imageWidth,currentAnim->c1.second / sprites->imageHeight);
        glVertex3f(-width/2,-height/2,0);
        glTexCoord2f(currentAnim->c2.first / sprites->imageWidth,currentAnim->c1.second / sprites->imageHeight);
        glVertex3f(width/2,-height/2,0);
        glTexCoord2f(currentAnim->c2.first / sprites->imageWidth,currentAnim->c2.second / sprites->imageHeight);
        glVertex3f(width/2,height/2,0);
    glEnd();
    glPopMatrix();
}

void Pig::jump(){

    body->ApplyForce(b2Vec2(0.0f,999999999.f),body->GetWorldCenter(),true);

}
