#include "system.h"
#include "bird.h"
#include "pig.h"
#include "platform.h"
#include "slingshot.h"

#define traverse(c,it) for( typeof(c.begin()) it = c.begin(); it!=c.end(); it++)

void System::initGame(){
    if(setup()){
        if(loadMedia()){
            initSprites();
            bool salir=false;
            SDL_Event e;
            while(!salir){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT){
                        salir = true;
                    }
                }
                renderGLobal();
                SDL_GL_SwapWindow(w);
            }
            cerrar();
        }
    }
}

void System::initSprites(){
    //Plataformas
    int nPlatforms;
    GLfloat x=0.f,y=350.f,z=50.f;//Valores iniciales:cambiar
    for(int i=1;i<=nPlatforms;i++){
        if(i%5==4){
            x=75.f;
            y-=65.f;
        }else{
            if(i%5==1){
                x=0.f;
                y-=65.f;
            }else{
                x+=200.f;
            }
        }
        platforms.push_back(new Platform(x,y,z,&iSprites[PLATFORM][PLATFORM_STONE]));
        canvas[z].push_back(platforms.end()-1);
    }

    //Pájaros
    x=-200.f;y=-400.f;z=30.f;
    birds.push_back(new Platform(x,y,z,&aSprites[BIRD][BIRD_YELLOW]);
    canvas[z].push_back(platforms.end()-1);
    //Chancho
    x=0.f;y=0.f;z=15.f;
    pig = new Pig(x,y,z,&aSprites[PIG][PIG_NORMAL]);
    canvas[z].push_back(pig);
}


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
    return success;
}

bool System::setupGL(){
    GLenum error=GL_NO_ERROR;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WINDOW_WIDTH/2,WINDOW_WIDTH/2,-WINDOW_HEIGHT/2,WINDOW_HEIGHT/2,-150,150);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f,0.f,0.f,1.f);
    glEnable(GL_TEXTURE_2D);

    if((error=glGetError())!=GL_NO_ERROR){
        cout<<"Error al inicializar OpenGL"<<endl;
        return false;
    }else{
        return true;
    }
}

void System::setdown(){
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_Quit();
}

bool System::loadMedia(){
    bool success= true;
    ifstream spritesCoords("SpriteCoordinates.txt");

    success = aSprites[PIG][NORMAL].loadTextureFromFile("images/normalPig.png");
    success = aSprites[PIG][NORMAL].loadSpriteMap(spritesCoords,PIG,PIG_NORMAL);

    success = aSprites[PIG][HELMET].loadTextureFromFile("images/pig_helmet.png");
    success = aSprites[PIG][HELMET].loadSpriteMap(spritesCoords,PIG,PIG_HELMET);

    success = aSprites[PIG][KING].loadTextureFromFile("images/pig_crown.png");
    success = aSprites[PIG][KING].loadSpriteMap(spritesCoords,PIG,PIG_KING);

    success = aSprites[BIRD][YELLOW].loadTextureFromFile("images/pajaro_amarillo.png");
    success = aSprites[BIRD][YELLOW].loadSpriteMap(spritesCoords,BIRD,BIRD_YELLOW,)

    success = aSprites[BIRD][RED].loadTextureFromFile("images/redBird.png");
    success = aSprites[BIRD][RED].loadSpriteMap(spritesCoords,BIRD,BIRD_RED);

    success = iSprites[PLATFORM][STONE].loadTextureFromFile("images/bloqueconcreto.png");
    success = iSprites[PLATFORM][STONE].loadSpriteMap(spritesCoords,PLATFORM,PLATFORM_STONE);

    spritesCoords.close();
    return success;
}




void System::renderGlobal{
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    traverse(canvas,sPair){
        traverse(sPair->second,sprite){
            sprite->draw();
        }
    }
}
