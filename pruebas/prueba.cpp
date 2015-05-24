#include <iostream>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <FreeImage.h>
#define par pair<float,float>

using namespace std;

bool iniciar();
bool iniciarGL();
bool loadMedia1();
bool loadMedia();
void cerrar();
void render();
GLuint loadTexture(string filenameString, GLenum minificationFilter = GL_LINEAR, GLenum magnificationFilter = GL_LINEAR)
{
    // Get the filename as a pointer to a const char array to play nice with FreeImage
    const char* filename = filenameString.c_str();

    // Determine the format of the image.
    // Note: The second paramter ('size') is currently unused, and we should use 0 for it.
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename , 0);

    // Image not found? Abort! Without this section we get a 0 by 0 image with 0 bits-per-pixel but we don't abort, which
    // you might find preferable to dumping the user back to the desktop.
    if (format == -1)
    {
        cout << "Could not find image: " << filenameString << " - Aborting." << endl;
        exit(-1);
    }

    // Found image, but couldn't determine the file format? Try again...
    if (format == FIF_UNKNOWN)
    {
        cout << "Couldn't determine file format - attempting to get from file extension..." << endl;

        // ...by getting the filetype from the filename extension (i.e. .PNG, .GIF etc.)
        // Note: This is slower and more error-prone that getting it from the file itself,
        // also, we can't use the 'U' (unicode) variant of this method as that's Windows only.
        format = FreeImage_GetFIFFromFilename(filename);

        // Check that the plugin has reading capabilities for this format (if it's FIF_UNKNOWN,
        // for example, then it won't have) - if we can't read the file, then we bail out =(
        if ( !FreeImage_FIFSupportsReading(format) )
        {
            cout << "Detected image format cannot be read!" << endl;
            exit(-1);
        }
    }

    // If we're here we have a known image format, so load the image into a bitap
    FIBITMAP* bitmap = FreeImage_Load(format, filename);

    // How many bits-per-pixel is the source image?
    int bitsPerPixel =  FreeImage_GetBPP(bitmap);

    // Convert our image up to 32 bits (8 bits per channel, Red/Green/Blue/Alpha) -
    // but only if the image is not already 32 bits (i.e. 8 bits per channel).
    // Note: ConvertTo32Bits returns a CLONE of the image data - so if we
    // allocate this back to itself without using our bitmap32 intermediate
    // we will LEAK the original bitmap data, and valgrind will show things like this:
    //
    // LEAK SUMMARY:
    //  definitely lost: 24 bytes in 2 blocks
    //  indirectly lost: 1,024,874 bytes in 14 blocks    <--- Ouch.
    //
    // Using our intermediate and cleaning up the initial bitmap data we get:
    //
    // LEAK SUMMARY:
    //  definitely lost: 16 bytes in 1 blocks
    //  indirectly lost: 176 bytes in 4 blocks
    //
    // All above leaks (192 bytes) are caused by XGetDefault (in /usr/lib/libX11.so.6.3.0) - we have no control over this.
    //
    FIBITMAP* bitmap32;
    if (bitsPerPixel == 32)
    {
        cout << "Source image has " << bitsPerPixel << " bits per pixel. Skipping conversion." << endl;
        bitmap32 = bitmap;
    }
    else
    {
        cout << "Source image has " << bitsPerPixel << " bits per pixel. Converting to 32-bit colour." << endl;
        bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
    }

    // Some basic image info - strip it out if you don't care
    int imageWidth  = FreeImage_GetWidth(bitmap32);
    int imageHeight = FreeImage_GetHeight(bitmap32);
    cout << "Image: " << filenameString << " is size: " << imageWidth << "x" << imageHeight << "." << endl;

    // Get a pointer to the texture data as an array of unsigned bytes.
    // Note: At this point bitmap32 ALWAYS holds a 32-bit colour version of our image - so we get our data from that.
    // Also, we don't need to delete or delete[] this textureData because it's not on the heap (so attempting to do
    // so will cause a crash) - just let it go out of scope and the memory will be returned to the stack.
    GLubyte* textureData = FreeImage_GetBits(bitmap32);

    // Generate a texture ID and bind to it
    GLuint tempTextureID;
    glGenTextures(1, &tempTextureID);
    glBindTexture(GL_TEXTURE_2D, tempTextureID);

    // Construct the texture.
    // Note: The 'Data format' is the format of the image data as provided by the image library. FreeImage decodes images into
    // BGR/BGRA format, but we want to work with it in the more common RGBA format, so we specify the 'Internal format' as such.
    glTexImage2D(GL_TEXTURE_2D,    // Type of texture
                 0,                // Mipmap level (0 being the top level i.e. full size)
                 GL_RGBA,          // Internal format
                 imageWidth,       // Width of the texture
                 imageHeight,      // Height of the texture,
                 0,                // Border in pixels
                 GL_BGRA,          // Data format
                 GL_UNSIGNED_BYTE, // Type of texture data
                 textureData);     // The image data to use for this texture

    // Specify our minification and magnification filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minificationFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnificationFilter);


    // Check for OpenGL texture creation errors
    GLenum glError = glGetError();
    if(glError)
    {
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

    // Unload the 32-bit colour bitmap
    FreeImage_Unload(bitmap32);

    // If we had to do a conversion to 32-bit colour, then unload the original
    // non-32-bit-colour version of the image data too. Otherwise, bitmap32 and
    // bitmap point at the same data, and that data's already been free'd, so
    // don't attempt to free it again! (or we'll crash).
    if (bitsPerPixel != 32)
    {
        FreeImage_Unload(bitmap);
    }

    // Finally, return the texture ID
    return tempTextureID;
}

void delay(float secs)
{
	float end = clock()/CLOCKS_PER_SEC + secs;
	while((clock()/CLOCKS_PER_SEC) < end);
}

SDL_Window *w = NULL;
SDL_GLContext glcontext;

GLuint texID;
GLint iWidth,iHeight;
pair<float,float> recorte[]={par(0.f,1.f),par(0.f,0.5f),par(0.25f,0.5f),par(0.25f,1.f)};
int cont = 1;

int main(int argc, char*argv[]){
    FreeImage_Initialise(true);
    if(iniciar()){
        if(loadMedia()){
            bool salir=false;
            SDL_Event e;
            while(!salir){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT){
                        salir = true;
                    }
                }
                render();
                SDL_GL_SwapWindow(w);
                //delay(0.001);
                //Sleep(10);
            }
            cerrar();
        }
    }
    FreeImage_DeInitialise();
    return 0;
}


bool iniciar(){
    bool success=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        success = false;
    }else{
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
        w = SDL_CreateWindow("W",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1300,700,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
        if(w == NULL){
            success = false;
        }
        glcontext = SDL_GL_CreateContext(w);
        if(glcontext == NULL){
            success = false;
        }
        if(!iniciarGL()){
            success = false;
        }
    }
    return success;
}

bool iniciarGL(){
    bool success=true;
    GLenum error = GL_NO_ERROR;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-650,650,-350,350,-150,150);
    if((error = glGetError()) != GL_NO_ERROR){
        success = false;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.f,0.f,0.f,1.f);


    if((error = glGetError()) != GL_NO_ERROR){
        success = false;
    }
    return success;
}

void cerrar(){
    SDL_DestroyWindow(w);
    w = NULL;
    SDL_Quit();
}

bool loadMedia1(){
    bool success=true;
    FREE_IMAGE_FORMAT format = FIF_UNKNOWN;
    FIBITMAP* image;
    format = FreeImage_GetFileType("emma.png",0);
    if(format==FIF_UNKNOWN){
        format = FreeImage_GetFIFFromFilename("emma.png");
        if(format==FIF_UNKNOWN){
            success = false;
        }
    }else{
        if(FreeImage_FIFSupportsReading(format)){
            image = FreeImage_Load(format,"emma.png");
            if(!image){
                success = false;
            }

            FIBITMAP* newimage;
            newimage = FreeImage_ConvertTo32Bits(image);
            GLubyte* imageData = FreeImage_GetBits(newimage);
            for(int i=0;i<10;i++){
                cout<<(int)imageData[i]<<endl;
            }
            iWidth=FreeImage_GetWidth(image);
            iHeight=FreeImage_GetHeight(image);
            cout<<" W: "<<iWidth<<" H: "<<iHeight<<endl;
            int iBPP = FreeImage_GetBPP(image);

            if(imageData == NULL || iWidth == 0 || iHeight==0){
                success= false;
            }

            glGenTextures(1,&texID);
            glBindTexture(GL_TEXTURE_2D,texID);


   //         glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,iWidth,iHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,imageData);
            gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, iWidth, iHeight, GL_RGBA, GL_UNSIGNED_BYTE, imageData );

            GLenum glError = glGetError();
            if(glError == GL_NO_ERROR){
                cout<<"a"<<endl;
            }
            if(glError != GL_NO_ERROR)
            {
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
                success = false;
            }
            FreeImage_Unload(image);
        }else{
            success = false;
        }
    }
    return success;
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texID);

    if(cont>1){
        for(int i=0;i<4;i++){
            recorte[i].first += 0.25f;
        }
    }
    if(cont==4){
        for(int i=0;i<4;i++){
            recorte[i].second -= 0.5f;
        }
        recorte[0].first=recorte[1].first=0;
        recorte[2].first=recorte[3].first=0.25;
    }
    if(cont==8){
        cont=1;
        for(int i=0;i<4;i++){
            recorte[i].second += 0.5f;
        }
        recorte[0].first=recorte[1].first=0;
        recorte[2].first=recorte[3].first=0.25;
    }
    cont++;
    glBegin(GL_QUADS);
        glTexCoord2f(recorte[0].first,recorte[0].second);
        glVertex3f(-42.5f,50.f,0.f);
        glTexCoord2f(recorte[1].first,recorte[1].second);
        glVertex3f(-42.5f,-50.f,0.f);
        glTexCoord2f(recorte[2].first,recorte[2].second);
        glVertex3f(42.5f,-50.f,0.f);
        glTexCoord2f(recorte[3].first,recorte[3].second);
        glVertex3f(42.5f,50.f,0.f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

bool loadMedia(){
    texID = loadTexture("sprites.png");
    return true;
}




