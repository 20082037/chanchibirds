#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <FreeImage.h>
#include <iostream>
#include <time.h>

using namespace std;

bool iniciar();
bool iniciarGL();
void cerrar();
void render();
SDL_Window *w = NULL;
SDL_GLContext glcontext;

GLfloat c=1.0;
clock_t ti,tf;
GLfloat despx=100.f,despy=-100.f;
GLfloat juanx=-100.f, juany=-100.f;
clock_t interval = 10000;


int main(int argc, char*argv[]){
    ti = clock();
    cout<<ti<<endl;
    if(iniciar()){
        bool salir=false;
        SDL_Event jordan;
        while(!salir){
            while(SDL_PollEvent(&jordan) != 0){
                if(jordan.type == SDL_QUIT){
                    salir = true;
                }else if(jordan.type == SDL_KEYDOWN){
                    if(jordan.key.keysym.sym == SDLK_LEFT){
                        despx += -5.f;
                    }else if(jordan.key.keysym.sym == SDLK_RIGHT){
                        despx += 5.f;
                    }else if(jordan.key.keysym.sym == SDLK_DOWN){
                        despy += -5.f;
                    }else if(jordan.key.keysym.sym == SDLK_UP){
                        despy += 5.f;
                    }else if(jordan.key.keysym.sym == SDLK_a){
                        juanx += -5.f;
                    }else if(jordan.key.keysym.sym == SDLK_d){
                        juanx += 5.f;
                    }else if(jordan.key.keysym.sym == SDLK_w){
                        juany += 5.f;
                    }else if(jordan.key.keysym.sym == SDLK_s){
                        juany += -5.f;
                    }
                }
            }
            render();
            SDL_GL_SwapWindow(w);
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
        w = SDL_CreateWindow("CHANCHI BIRDS",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1300,700,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
        if(w == NULL){
            cout<<"Error."<<endl;
            return false;
        }
        glcontext = SDL_GL_CreateContext(w);
        if(glcontext == NULL){
            cout<<"Error :("<<endl;
            return false;
        }
        if(!iniciarGL()){
            cout<<"Error :("<<endl;
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
//    gluPerspective(60.0,1366/768,0.0,-0.05);
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"Error :("<<endl;
        return false;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"Error :("<<endl;
        return false;
    }
    glClearColor(0.f,0.f,0.f,1.f);
    if((error = glGetError()) != GL_NO_ERROR){
        cout<<"Error :("<<endl;
        return false;
    }
    return true;
}

void cerrar(){
    SDL_DestroyWindow(w);
    w = NULL;
    SDL_Quit();
}

void render(){
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_QUADS);
        glColor3f(1.f,0.f,1.f);
        glVertex3f(-50.f,50.f,0.f);
        glVertex3f(-50.f,-50.f,0.f);
        glVertex3f(50.f,-50.f,0.f);
        glVertex3f(50.f,50.f,0.f);
    glEnd();
    glPushMatrix();

    tf = clock();
    clock_t dt;
    dt = tf-ti;
    cout<<" x : "<<dt<<endl;
    static int count=0;
    count += dt;
    if(count > interval){
        count =0;
        cout<<"HOLI"<<endl;
        if(c==1.f){
            c=0.f;
        }else{
            c=1.f;
        }
    }

    swap(ti,tf);
    glTranslatef(despx,despy,0.f);
    glBegin(GL_QUADS);
        glColor3f(1.f,0.f,1.f);
        glVertex3f(-50.f,50.f,0.f);
        glVertex3f(-50.f,-50.f,0.f);
        glVertex3f(50.f,-50.f,0.f);
        glVertex3f(50.f,50.f,0.f);
    glEnd();

    glPopMatrix();


    glPushMatrix();
    glTranslatef(juanx,juany,0.f);
    glBegin(GL_QUADS);
        glColor3f(c,0.f,1.f);
        glVertex3f(-50.f,50.f,-5.f);
        glVertex3f(-50.f,-50.f,-5.f);
        glVertex3f(50.f,-50.f,-5.f);
        glVertex3f(50.f,50.f,-5.f);
    glEnd();
    glPopMatrix();

}
