#include "pig.h"

Pig::Pig(GLfloat xi,GLfloat yi,GLfloat zi,AnimateSpriteSheet* ssheet, b2World* world, int wWidth){//Provisional, se debería proveer direction y speed
    z=zi;
    sprites = ssheet;
    state=PIG_HEALTHY;
    currentAnim=sprites->states[state].begin();
    width=currentAnim->c2.second - currentAnim->c1.second;
    height=currentAnim->c2.first - currentAnim->c1.first;
    scale = 1/20.f;
    height = scale*wWidth*height / width;
    width = scale*wWidth;

    dt = 0, ti=clock();



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

    shape.ComputeMass(&massDa, fixture.density);

}

void Pig::animate(){

    if(currentAnim==--sprites->states[state].end()){
        currentAnim=sprites->states[state].begin();
    }else{
        currentAnim++;
    }
}

void Pig::draw(){
    dt += clock()-ti;
    ti = clock();//No habra pasado mucho tiempo
    if(dt>100000){
        animate();
        dt = 0;
    }
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    cout<<"PIG"<<endl;
    glTranslatef(body->GetPosition().x,body->GetPosition().y,z);

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
    glDisable(GL_BLEND);
    glPopMatrix();
}

void Pig::jump(){


    body->ApplyForce(b2Vec2(0.0f,5000000.f),body->GetWorldCenter(),true);
}

void Pig::slideLeft(){
    body->ApplyForce(b2Vec2(-5000000.f,0.f),body->GetWorldCenter(),true);
}
void Pig::slideRight(){
    body->ApplyForce(b2Vec2(5000000.f,0.f),body->GetWorldCenter(),true);
}

void Pig::down(){
    body->ApplyForce(b2Vec2(0.f,-5000000.f),body->GetWorldCenter(),true);
}
