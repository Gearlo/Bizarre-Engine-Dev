#ifndef B_RENDER_INFO
#define B_RENDER_INFO

class BRenderInfo{ //Todo: cambiarlo por BRenderOptions
public:
    unsigned int fps;
    unsigned int maxFps;
    bool disabledTextureFilter;
    bool disableTextureCompression;

private:
    BRenderInfo(void):
    fps(0u),
    maxFps(60u),
    disabledTextureFilter(false),
    disableTextureCompression(true)
    {}

public:
    static BRenderInfo * getInstance(void){ static BRenderInfo instance; return &instance; }

    void changeRenderer(const char * name);
};


#endif