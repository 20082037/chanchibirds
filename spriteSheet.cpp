#include "spriteSheet.h"

bool SpriteSheet::loadTextureFromFile(string filenameString){
	bool success=true;
    GLenum minificationFilter = GL_LINEAR;
    GLenum magnificationFilter = GL_LINEAR;

    const char* filename = filenameString.c_str();

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename , 0);

    if (format == -1){
        cout << "Could not find image: " << filenameString << " - Aborting." << endl;
        success = false;
    }
    else if (format == FIF_UNKNOWN){
        cout << "Couldn't determine file format - attempting to get from file extension..." << endl;
        format = FreeImage_GetFIFFromFilename(filename);

        if ( !FreeImage_FIFSupportsReading(format) ){
            cout << "Detected image format cannot be read!" << endl;
            success = false;
        }
    }else{
        FIBITMAP* bitmap = FreeImage_Load(format, filename);
        int bitsPerPixel =  FreeImage_GetBPP(bitmap);
        FIBITMAP* bitmap32;

        if (bitsPerPixel == 32){
            bitmap32 = bitmap;
        }
        else{
            bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
        }

        imageWidth  = FreeImage_GetWidth(bitmap32);
        imageHeight = FreeImage_GetHeight(bitmap32);
        GLubyte* textureData = FreeImage_GetBits(bitmap32);

        glGenTextures(1, &(this->texID));
        glBindTexture(GL_TEXTURE_2D, this->texID);
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
        if(glError){
            success = false;
            cout << "There was an error loading the texture: "<< filenameString << endl;
            switch (glError){
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
        }
        else{
            FreeImage_Unload(bitmap32);

            if (bitsPerPixel != 32){
                FreeImage_Unload(bitmap);
            }
        }
    }
    return success;
}

float SpriteSheet::stof(string s){
	float result;
	int pos = s.find(".");
	int size = s.size();
	if(pos != string::npos){
		int intPart = atoi(s.substr(0,pos+1).c_str());
		float floatPart = atoi(s.substr(pos+1,size-pos-1).c_str()) / pow(10,size-pos-1);
		result = intPart + floatPart;
	}else{
		result = atoi(s.c_str());
	}
	return result;
}

