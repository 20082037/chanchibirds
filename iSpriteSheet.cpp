#include "iSpriteSheet.h"

bool InanimateSpriteSheet::loadSpriteMap(ifstream &file,int TAG,int TAG_TYPE){
    bool success=true;
    string line;
    if(file.is_open()){
        vector<float> coords;
        SpriteCoords sc;

        bool isTheSector=true;
        bool isTheSprite=false;

        while(getline(file,line) and isTheSector){
            int i=0;

            size_t posi=0,posf;
            posf = line.find("\t");
            while(posf != string::npos){
                coords.push_back(stof(line.substr(posi,posf-posi)));
                posi = posf+1;
                posf = line.find("\t",posi);

                i++;
                if(i==2){
                    if(coords[0]!=TAG or coords[1]!=TAG_TYPE){
                        if(isTheSprite){
                            isTheSector=false;
                            isTheSprite=false;
                        }
                        break;
                    }else{
                        isTheSprite=true;
                    }
                }
            }
            if(isTheSprite){
                int sz = coords.size();
                for(int j=3;j<sz;j++){
                    if(j%4==3){
                        sc.c1.first=coords[j];
                    }else if(j%4==0){
                        sc.c1.second=coords[j];
                    }else if(j%4==1){
                        sc.c2.first=coords[j];
                    }else if(j%4==2){
                        sc.c2.second=coords[j];
                    }
                }
                states[coords[2]] = sc;
                anim.clear();
            }
            coords.clear();
        }
        file.close();
    }else{
        cout<<"No se pudo abrir el archivo de coordenadas."<<endl;
        success = false;
    }
    return 0;
}

