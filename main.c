/*  English File-Header
 *
 * This file is part of jDOOM.
 *
 * jDOOM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * jDOOM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with jDOOM.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*  Deutscher Dateikopf
 *
 * Diese Datei ist Teil von jDOOM.
 *
 * jDOOM ist Freie Software: Sie können es unter den Bedingungen
 * der GNU General Public License, wie von der Free Software Foundation,
 * Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 * veröffentlichten Version, weiter verteilen und/oder modifizieren.
 *
 * jDOOM wird in der Hoffnung, dass es nützlich sein wird, aber
 * OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 * Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 * Siehe die GNU General Public License für weitere Details.
 *
 * Sie sollten eine Kopie der GNU General Public License zusammen mit jDOOM
 * erhalten haben. Wenn nicht, siehe <https://www.gnu.org/licenses/>.
 *
 */
#include "main.h"

int main(int argc, char* argv[]) {

  if ( width > 7680 || height > 4320 ) {
      fprintf(stderr, "Unable to init Render\n");
      fprintf(stderr, "This Version support only\n");
      fprintf(stderr, "up to 7680x4320 ( 8k )\n");
      fprintf(stderr, "... end\n");
      return 0;
  };

  clock_t start, stop;    // Timers
  int delay;              // time between to frames
  int fps;                // frames per secound
  char fpsS[12];          // fps as string
  start = clock();        // Start first Timer
  int exit = 0;           // exittrigger > 0 = run, 1 = exit per key, 2 = exit per window

  SDL_Surface* screen;
  SDL_Event event;
  int x_movement;
  int y_movement;
  int a_movement;
  int m_movement;
  int fastmove;
  if ( sizeof(int) != 4 ) {
    fprintf(stderr, " fatal: sizeof(int) != 4 > exit\n");
    return 0;
  };
  if ( initOutput(OutputDriver) == 0 ) {               // Init the outputsystem
    fprintf(stderr, " fatal: cannot init the OutputDriver > exit\n");
    return 0;                                          // if failed > exit
  };
  screen = openOutput(OutputDriver,width,height);
  if ( screen == 0 ) {                                 // Open the outputsystem
    fprintf(stderr, " fatal: cannot open the OutputDriver > exit\n");
    return 0;                                          // if failed > exit
  };

  DummyTex(0,32,RGB(85,85,85),RGB(170,170,170));
  DummyTex(1,32,RGB(0,0,170),RGB(85,85,255));
  DummyTex(2,32,RGB(0,170,0),RGB(85,255,85));
  DummyTex(3,32,RGB(170,0,0),RGB(255,85,85));
  DummyTex(4,32,RGB(0,170,170),RGB(85,255,255));
  DummyTex(5,32,RGB(170,170,0),RGB(255,255,85));
  DummyTex(6,32,RGB(170,0,170),RGB(255,85,255));

  SDL_EnableKeyRepeat(0,0);
  // Main-Loop
  do {
    // Timer
    stop = clock();
    delay = stop - start;
    start = clock();
    fps = 1000000 / delay;
    sprintf(fpsS,"%d",fps);
    setOutputTitle(OutputDriver,fpsS);
    m_movement = 0;
    // EventHandler
    while ( SDL_PollEvent( &event ) ) {
      switch( event.type ) {
        case SDL_QUIT:
          exit = 2; // EXIT by window
          break;
        case SDL_VIDEORESIZE:
          width = event.resize.w;
          height = event.resize.h;
          screen = resizeOutput(OutputDriver,width,height);
          if ( screen == 0 ) {
            fprintf(stderr, " fatal: cannot resize the OutputDriver > exit\n");
            return 0;
          };
          break;
        case SDL_MOUSEMOTION:
          m_movement = event.motion.x;
          break;
        case SDL_KEYDOWN:
          switch( event.key.keysym.sym ){
            case SDLK_ESCAPE:
              exit = 1; // EXIT by key
              break;
            case SDLK_TAB:
              mouseLook = 1 - mouseLook;
              break;
            default:
              break;
          }
        default:
          break;
      }
    }

    x_movement = 0;
    y_movement = 0;
    a_movement = 0;
    fastmove = 0;
    Uint8 *keys = SDL_GetKeyState(NULL);
    if (keys[SDLK_a]) {
        x_movement = -1;
    }
    if (keys[SDLK_d]) {
        x_movement =  1;
    }
    if (keys[SDLK_w]) {
        y_movement =  1;
    }
    if (keys[SDLK_s]) {
        y_movement = -1;
    }
    if (keys[SDLK_UP]) {
        y_movement =  1;
    }
    if (keys[SDLK_DOWN]) {
        y_movement = -1;
    }
    if (keys[SDLK_LEFT]) {
        a_movement =  1;
    }
    if (keys[SDLK_RIGHT]) {
        a_movement = -1;
    }
    if (keys[SDLK_e]) {
        fastmove = 1;
    }

    // MoveHandler
    updatePlayer(delay/1000,x_movement,y_movement,a_movement,m_movement,0,fastmove);

    // ScreenHandler
    if ( startDrawing(OutputDriver,screen) != 1 ) {
      fprintf(stderr, " fatal: cannot draw on the OutputDriver > exit\n");
      return 0;
    }
    clearScene();

    // Rendering
    DrawFlatPOV(-100,200,100,200,100,100,-100,100,50,0);

    stopDrawing(OutputDriver,1);
    outputStuff(OutputDriver);
  } while ( exit == 0 );
  // Cleanup
  SDL_Quit();
};


