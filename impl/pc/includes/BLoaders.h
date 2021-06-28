#ifndef _U_PC_LOADERS_H_
#define _U_PC_LOADERS_H_


bool xmlArmatureAnimLoad(const char * filename, void * data);
bool xmlTextureAnimLoad(const char * filename, void * data);
bool xmlMaterialAnimLoad(const char * filename, void * data);
bool xmlMeshLoad(const char * filename, void * data);

bool B_loadImage(const char * filename, void * data);
bool B_loadFont(const char * filename, void * data /*, void * arg */ );
bool B_loadBinFont(const char * filename, void * data);
//bool B_loadSound(const char * filename, void * data);
bool B_loadWavSound(const char * filename, void * data);
bool B_loadModMusic(const char * filename, void * data);

#endif