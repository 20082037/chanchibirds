#include <iostream>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <FreeImage.h>
#include "system.h"
#include "bird.h"
#include "pig.h"
#include "platform.h"
#include "slingshot.h"


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
//    map<int,GLuint> textures;
    //map<TAG,TEXTUREID>

//    map<int,map<int,pair<GLfloat,GLfloat>* > > sprites;
    //map<TAG,map<STATE,COORDENADAS<GLfloat,GLfloat>* > >
    loadTexture("images/normalPig.png",textures[PIG]);
    loadTexture("images/redBird.png",textures[BIRD]);
    loadTexture("",textures[PLATFORM]);
    loadTexture("",textures[SLINGSHOT]);

    pair<GLfloat,GLfloat>* spriteCoords;

    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(0.f,1.f); spriteCoords[1]=make_pair(0.f,294.34f/374.f); spriteCoords[2]=make_pair(129.3f/388.f,294.34f/374.f); spriteCoords[3]=make_pair(129.3f/388.f,1.f);
    sprites[PIG][Pig::NORMAL] =spriteCoords;

    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(,); spriteCoords[1]=make_pair(,); spriteCoords[2]=make_pair(,); spriteCoords[3]=make_pair(,);
    sprites[PIG][Pig::DAMAGED1] =spriteCoords;

    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(,); spriteCoords[1]=make_pair(,); spriteCoords[2]=make_pair(,); spriteCoords[3]=make_pair(,);
    sprites[PIG][Pig::DAMAGED2] =spriteCoords;

    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(,); spriteCoords[1]=make_pair(,); spriteCoords[2]=make_pair(,); spriteCoords[3]=make_pair(,);
    sprites[PIG][Pig::DEAD] =spriteCoords;


    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(,); spriteCoords[1]=make_pair(,); spriteCoords[2]=make_pair(,); spriteCoords[3]=make_pair(,);
    sprites[BIRD][Bird::NORMAL] =spriteCoords;

    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(,); spriteCoords[1]=make_pair(,); spriteCoords[2]=make_pair(,); spriteCoords[3]=make_pair(,);
    sprites[BIRD][Bird::HIT] =spriteCoords;


    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(,); spriteCoords[1]=make_pair(,); spriteCoords[2]=make_pair(,); spriteCoords[3]=make_pair(,);
    sprites[PLATFORM][Platform::NORMAL] =spriteCoords;


    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(,); spriteCoords[1]=make_pair(,); spriteCoords[2]=make_pair(,); spriteCoords[3]=make_pair(,);
    sprites[SLINGSHOT][Slingshot::ANGLE1] =spriteCoords;

    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(,); spriteCoords[1]=make_pair(,); spriteCoords[2]=make_pair(,); spriteCoords[3]=make_pair(,);
    sprites[SLINGSHOT][Slingshot::ANGLE2] =spriteCoords;

    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(,); spriteCoords[1]=make_pair(,); spriteCoords[2]=make_pair(,); spriteCoords[3]=make_pair(,);
    sprites[SLINGSHOT][Slingshot::ANGLE3] =spriteCoords;

    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(,); spriteCoords[1]=make_pair(,); spriteCoords[2]=make_pair(,); spriteCoords[3]=make_pair(,);
    sprites[SLINGSHOT][Slingshot::ANGLE4] =spriteCoords;

    spriteCoords = new pair<GLfloat,GLfloat>[4];
    spriteCoords[0]=make_pair(,); spriteCoords[1]=make_pair(,); spriteCoords[2]=make_pair(,); spriteCoords[3]=make_pair(,);
    sprites[SLINGSHOT][Slingshot::ANGLE5] =spriteCoords;

    if(textures[PIG] == NULL || textures[BIRD] == NULL || textures[PLATFORM] == NULL || textures[SLINGSHOT] == NULL){
        cout<<"Error al cargar alguna imagen."<<endl;
        return false;
    }else{
        return true;
    }
}

System::System(){
    if(loadMedia()){
        //Podriamos generar una pos. inicial aleatoria
        pair<GLfloat,GLfloat>
        pig = new Pig(0.f,0.f,0.f,374.f-294.34f,129.3f,PIG,textures[PIG],Pig::NORMAL);
        slingshot = new Slingshot();
    }
}

void System::loadTexture(string filenameString, GLuint* tempTextureID)
{
    GLenum minificationFilter = GL_LINEAR;
    GLenum magnificationFilter = GL_LINEAR;

    const char* filename = filenameString.c_str();

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename , 0);

    if (format == -1)
    {
        cout << "Could not find image: " << filenameString << " - Aborting." << endl;
        tempTextureID = NULL;
    }
    else if (format == FIF_UNKNOWN)
    {
        cout << "Couldn't determine file format - attempting to get from file extension..." << endl;

        format = FreeImage_GetFIFFromFilename(filename);

        if ( !FreeImage_FIFSupportsReading(format) )
        {
            cout << "Detected image format cannot be read!" << endl;
            tempTextureID = NULL;
        }
    }else{
        FIBITMAP* bitmap = FreeImage_Load(format, filename);

        int bitsPerPixel =  FreeImage_GetBPP(bitmap);

        FIBITMAP* bitmap32;
        if (bitsPerPixel == 32)
        {
            //cout << "Source image has " << bitsPerPixel << " bits per pixel. Skipping conversion." << endl;
            bitmap32 = bitmap;
        }
        else
        {
            //cout << "Source image has " << bitsPerPixel << " bits per pixel. Converting to 32-bit colour." << endl;
            bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
        }

        int imageWidth  = FreeImage_GetWidth(bitmap32);
        int imageHeight = FreeImage_GetHeight(bitmap32);
        //cout << "Image: " << filenameString << " is size: " << imageWidth << "x" << imageHeight << "." << endl;

        GLubyte* textureData = FreeImage_GetBits(bitmap32);

    //    GLuint tempTextureID;
        glGenTextures(1, tempTextureID);
        glBindTexture(GL_TEXTURE_2D, *tempTextureID);

        glTexImage2D(GL_TEXTURE_2D,    // Type of texture
                     0,                // Mipmap level (0 being the top level i.e. full size)
                     GL_RGBA,          // Internal format
                     imageWidth,       // Width of the texture
                     imageHeight,      // Height of the texture,
                     0,                // Border in pixels
                     GL_BGRA,          // Data format
                     GL_UNSIGNED_BYTE, // Type of texture data
                     textureData);     // The image data to use for this texture

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minificationFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnificationFilter);

        GLenum glError = glGetError();
        if(glError)
        {
            tempTextureID = NULL;
            cout << "There was an error loading the texture: "<< filenameString << endl;
            switch (glError)
            {
                case GL_INVALID_ENUM:
                    cout << "Invalid enum." << endl;
                    break;

                case GL_INVALID_VALUE:
                    cout << "Invalid value." << endl;
                    break;

                case GL_INVALID_OPERATION:
                    cout << "Invalid operation." << endl;

                default:
                    cout << "Unrecognised GLenum." << endl;
                    break;
            }
            cout << "See https://www.opengl.org/sdk/docs/man/html/glTexImage2D.xhtml for further details." << endl;
        }
        else
        {
            FreeImage_Unload(bitmap32);

            if (bitsPerPixel != 32)
            {
                FreeImage_Unload(bitmap);
            }
        }
    }
}
