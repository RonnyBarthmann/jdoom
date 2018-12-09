// Mainoptions
int    width = 800;      // window or screen width
int    height = 600;     // window or screen height
float  px = 0, py = 0, ph = 100, pa = 0;
int    MouseSupport = 1; // Grab the mouse
double MouseFactor = 0.5; // Mouse speed
int    OutputDriver = 0; // 0 = SDL
                         // 1 = SDL Fullscreen ( not implimented yet )
                         // 2 = FBdev ( Z:\dev\fb0 ) ( not implimented yet )

// Debugoptions
int    RenderFailsafe = 1;
int    DebugModeWall = 1;   // if 1, draw outlines and corners on walls
int    DebugModeFlat = 1;   // if 1, draw outlines and corners on flats and cellings
int    DebugModeSprite = 1; // if 1, draw outlines and corners on sprites
int    RenderWallTex = 1;   // if 0, render flat color on walls
int    RenderFlatTex = 1;   // if 0, render flat color on flats and cellings
int    RenderSpriteTex = 1; // if 0, render flat color on sprites
