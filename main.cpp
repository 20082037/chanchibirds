#include <iostream>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Box2D/Box2D.h>
#include<stdio.h>

using namespace std;

bool iniciar();
bool iniciarGL();
void cerrar();
void render(b2World &world,float32 timeSte, int32 velocityIteracion, int32 positionIteracion,b2Body* Cuerpo1,b2Body* Cuerpo2,/*b2Body* Cuerpo3,*/b2Body* Suelo);

SDL_Window *w = NULL; //Creamos la ventana
SDL_GLContext glcontext;//Crea el oontexto dentro de sdl


int main(int argc, char*argv[]){
    if(iniciar()){
        //------CREACION DEL MUNDO--------
        b2Vec2 gravity(0.0f,-10.0f);//Definir la gravedad
        b2World world(gravity); //Crear el mundo con parametro de la gravedad


//--------------------------------------CREACION DEL CUADRADO----------------------------------------------------------
        b2BodyDef Caja1;//Creamos el objeto
        Caja1.position.Set(-400.0f,-249.0f);//Colocando la posicion del cuerpo dinamico
        Caja1.type=b2_dynamicBody;//Volvemos el  objeto estatico en obetejo dinamico
        b2Body* Cuerpo1=world.CreateBody(&Caja1);//Coloca al cuerpo dinamico en el Mundo

/*        b2MassData* data;
        data->mass=45.0f;
        Cuerpo1->SetMassData(data);*/

        b2PolygonShape Poligono1; //Creacion de un poligono
        Poligono1.SetAsBox(50.0f,50.f); //TAMAÑOS

        b2FixtureD<c3ef Accesorios1;
        Accesorios1.shape=&Poligono1;
        Accesorios1.density=10.0f;
        Accesorios1.restitution=5.6f;

        Cuerpo1->CreateFixture(&Accesorios1); //CUERPO1 B2BODY

        float impulse=Cuerpo1->GetMass()*10;
        Cuerpo1->ApplyLinearImpulse(b2Vec2(0,impulse),Cuerpo1->GetWorldCenter(),true);

//------------------------------CREACION DEL SEGUNDO CUADRADO--------------------------------------------------------

        b2BodyDef Caja2;//Creamos el objeto
        Caja2.position.Set(200.0f,-249.0f);//Colocando la posicion del cuerpo dinamico
        Caja2.type=b2_dynamicBody;//Volvemos el  objeto estatico en obetejo dinamico
        b2Body* Cuerpo2=world.CreateBody(&Caja2);//Coloca al cuerpo dinamico en el Mundo

        b2PolygonShape Poligono2; //Creacion de un poligono
        Poligono2.SetAsBox(50.0f,50.0f); //creacion de un poligono en el sueloe

        //CAJITA2.ComputeMass(b2MassData* jordan, float32 hola.density);
        //b2MassData* jordan;

        b2FixtureDef Accesorios2;
        Accesorios2.shape=&Poligono2;
        Accesorios2.density=999999999999.0f;
        Accesorios2.restitution=0.6f;

        Cuerpo2->CreateFixture(&Accesorios2);


//-----------------------------CREACION DEL TERCER CUERPO----------------------------------------------------------------
       /* b2BodyDef Caja3;//Creamos el objeto
        Caja3.position.Set(90.0,0.0f);//Colocando la posicion del cuerpo dinamico
        Caja3.type=b2_dynamicBody;//Volvemos el  objeto estatico en obetejo dinamico
        b2Body* Cuerpo3=world.CreateBody(&Caja3);//Coloca al cuerpo dinamico en el Mundo

        b2CircleShape Circulo;


        Cuerpo2->CreateFixture(&Poligono3,0.0f);
        b2FixtureDef Accesorios3;
        Accesorios2.shape=&Poligono3;
        Accesorios2.density=0.0f;
        Accesorios2.restitution=0.0f;

*/
//---------------------------------------CUERPO ESTATICO--------------------------------------------------------------
        b2BodyDef Rectangulo;//Creamos el objeto
        Rectangulo.type=b2_staticBody;//Volvemos el  objeto estatico en obetejo dinamico
        Rectangulo.position.Set(0.0f,-300.0f);//Colocando la posicion del cuerpo dinamico
        b2Body* Suelo=world.CreateBody(&Rectangulo);//Coloca al cuerpo dinamico en el Mundo

        b2PolygonShape Terreno; //Creacion de un poligono
        Terreno.SetAsBox(800.0f,1.0f); //creacion de un poligono en el suelo

        Suelo->CreateFixture(&Terreno ,0.0f);

//---------------------------------------------ITERACIONES---------------------------------------------------------
        float32 timeSte = 1.0f/60.0f;

        int32 velocityIteracion=8;
        int32 positionIteracion=3;
//------------------------------------------------------------------------------------------------------
        bool salir=false;
        SDL_Event jordan;
        while(!salir){
            while(SDL_PollEvent(&jordan) != 0){//el próximo evento se elimina de la cola y se almacena en el SDL_Event.
                if(jordan.type == SDL_QUIT){//DEVUELVE EL TIPO DE DATO
                    salir = true;
                }
            }
            render(world,timeSte,velocityIteracion,positionIteracion,Cuerpo1,Cuerpo2,Suelo);

            SDL_GL_SwapWindow(w);//CAMBIO DE VENTANA
        }
        cerrar();
    }
    return 0;
}

bool iniciar(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        cout<<"Error"<<endl;
        return false;
    }else{
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
        w = SDL_CreateWindow("CHANCHY BIRDS",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1300,700,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
        if(w == NULL){
            cout<<"Error."<<endl;
            return false;
        }
        glcontext = SDL_GL_CreateContext(w);
        if(glcontext == NULL){
            cout<<"ERROR!!!"<<endl;
            return false;
        }
        if(!iniciarGL()){
            cout<<"ERROR!!!"<<endl;
            return false;
        }
    }
    return true;
}

bool iniciarGL(){
    GLenum error = GL_NO_ERROR;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-650,650,-350,350,-150,150);
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"ERROR!!!"<<endl;
        return false;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();//CARGA LA mATRIZ iDENTIDAD
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"ERROR!!!"<<endl;
        return false;
    }
    glClearColor(0.f,0.f,0.f,1.f);
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"ERROR!!!"<<endl;
        return false;
    }
    return true;
}

void cerrar(){
    SDL_DestroyWindow(w);//DESTRUYE LA VENTANA
    w = NULL;
    SDL_Quit();
}

void render(b2World &world,float32 timeSte, int32 velocityIteracion, int32 positionIteracion,b2Body* CUERPO, b2Body* CUERPO_CUADRADO, b2Body* body)
{

    world.Step(timeSte,velocityIteracion, positionIteracion);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-2.0);

    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex3f(body->GetPosition().x-650.f,body->GetPosition().y+1.f,0.f);
        glVertex3f(body->GetPosition().x-650.f,body->GetPosition().y-1.f,0.f);
        glVertex3f(body->GetPosition().x+650.f,body->GetPosition().y-1.f,0.f);
        glVertex3f(body->GetPosition().x+650.f,body->GetPosition().y+1.f,0.f);
    glEnd();

     glBegin(GL_QUADS);
        glColor3f(1.0,0.0,1.0);
        glVertex3f(CUERPO_CUADRADO->GetPosition().x-50.f,CUERPO_CUADRADO->GetPosition().y+50.f,0.f);
        glVertex3f(CUERPO_CUADRADO->GetPosition().x-50.f,CUERPO_CUADRADO->GetPosition().y-50.f,0.f);
        glVertex3f(CUERPO_CUADRADO->GetPosition().x+50.f,CUERPO_CUADRADO->GetPosition().y-50.f,0.f);
        glVertex3f(CUERPO_CUADRADO->GetPosition().x+50.f,CUERPO_CUADRADO->GetPosition().y+50.f,0.f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.0,1.0,1.8);
        glVertex3f(CUERPO->GetPosition().x-50.f,CUERPO->GetPosition().y+50.f,0.f);
        glVertex3f(CUERPO->GetPosition().x-50.f,CUERPO->GetPosition().y-50.f,0.f);
        glVertex3f(CUERPO->GetPosition().x+50.f,CUERPO->GetPosition().y-50.f,0.f);
        glVertex3f(CUERPO->GetPosition().x+50.f,CUERPO->GetPosition().y+50.f,0.f);
    glEnd();

}
