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
  int fastmove;
  if ( sizeof(int) != 4 ) {
    fprintf(stderr, " fatal: sizeof(int) != 4 > exit");
    return 0;
  };
  if ( initOutput(OutputDriver) == 0 ) {               // Init the outputsystem
    fprintf(stderr, " fatal: cannot init the OutputDriver > exit");
    return 0;                                          // if failed > exit
  };
  screen = openOutput(OutputDriver,width,height);
  if ( screen == 0 ) {                                 // Open the outputsystem
    fprintf(stderr, " fatal: cannot open the OutputDriver > exit");
    return 0;                                          // if failed > exit
  };

  // Main-Loop
  do {
    // Timer
    stop = clock();
    delay = stop - start;
    start = clock();
    fps = 1000000 / delay;
    sprintf(fpsS,"%d",fps);
    setOutputTitle(OutputDriver,fpsS);
    // for ( int i = 0 ; i < 1000000 ; i++ ) i++;

    // EventHandler
    while ( SDL_PollEvent( &event ) ) {
      switch( event.type ) {
        case SDL_QUIT:
          exit = 2; // EXIT by window
          break;
        case SDL_KEYDOWN:
          switch( event.key.keysym.sym ){
            case SDLK_a:
              x_movement = -1;
              break;
            case SDLK_d:
              x_movement =  1;
              break;
            case SDLK_w:
            case SDLK_UP:
              y_movement =  1;
              break;
            case SDLK_s:
            case SDLK_DOWN:
              y_movement = -1;
              break;
            case SDLK_LEFT:
              a_movement =  1;
              break;
            case SDLK_RIGHT:
              a_movement = -1;
              break;
            case SDLK_e:
              fastmove = 1;
              break;
            case SDLK_ESCAPE:
              exit = 1; // EXIT by key
            default:
              break;
          }
        case SDL_KEYUP:
          switch( event.key.keysym.sym ){
            case SDLK_a:
              x_movement = 0;
              break;
            case SDLK_d:
              x_movement = 0;
              break;
            case SDLK_w:
            case SDLK_UP:
              y_movement = 0;
              break;
            case SDLK_s:
            case SDLK_DOWN:
              y_movement = 0;
              break;
            case SDLK_LEFT:
              a_movement = 0;
              break;
            case SDLK_RIGHT:
              a_movement = 0;
              break;
            case SDLK_e:
              fastmove = 0;
              break;
            default:
              break;
          }
        default:
          break;
      }
    }

    // MoveHandler
    // insert here the Sin() Cos() XY shit...

    // ScreenHandler
    if ( startDrawing(screen) != 1 ) {
      fprintf(stderr, " fatal: cannot draw on the OutputDriver > exit");
      return 0;
    }
    plotPixel(screen,px,1,255);
    stopDrawing(screen,1);
  } while ( exit == 0 );
  // Cleanup
  SDL_Quit();
};


