#include <iostream>
#include "system.h"
#include <SDL2/SDL.h>
#include <GL/gl.h>


bool System::setup(){

    bool success=true;

    if(SDL_Init(SDL_INIT_VIDEO)>=0){
        SDL_GL_SetAttribute(SDL_GL_CONTENT_MAJOR_VERSION,2);
        SDL_GL_SetAttribute(SDL_GL_CONTENT_MINOR_VERSION,1);
        window=SDL_CreateWindow("Chanchi Birds",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDHT,HEIGHT,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

        if(window!=NULL){
            glcontext=SDL_GL_CreateContext(window);
            if(glcontext!=NULL){
                if(!setupGL()){
                    success=false;
                }
            }else{
                cout<<"Fallo al crear contexto OpenGL"<<endl;
            }
        }else{
            cout<<"Fallo en crear la ventana"<<endl;
            success=false;
        }
    }else{
        cout<<"Fallo en inicializacion de SDL"<<endl;
        success=false;
    }
}

bool System::setupGL(){

    GLenum error=GL_NO_ERROR;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WINDOW_WIDHT/2,WINDOW_WIDHT/2,-WINDOW_HEIGHT/2,WINDOW_HEIGHT/2,-150,150);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f,0.f,0.f,1.f);
    if((error=glGetError())!=GL_NO_ERROR){
        cout<<"Error al inicializar OpenGL"<<endl;
        return false;
    }else{
        return true;
    }
}

void System::setdown(){
    SDL_DestroyWindow(window);
    w=NULL;
    SDL_Quit();
}

bool System::loadMedia(){



}
