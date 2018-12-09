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

int RGB(int r, int g, int b) {
  return r|g<<8|b<<16;
}

int initOutput(int output) {
  switch (output) {
    case 0: // SDL window or
    case 1: // SDL fullscreen
      if(SDL_Init(SDL_INIT_VIDEO) != -1) {                          // init the SDL subsystem
        fprintf(stderr, "init SDL successful\n");
        return 1;
      } else {
        fprintf(stderr, "Cannot init SDL > ");
        fprintf(stderr, SDL_GetError());
        fprintf(stderr, "\n");
        return 0;
      }; break;
    case 2: // FBdev
      fprintf(stderr, "Cannot init FBdev > not implimented yet\n");
      return 0;
      break;
  };
  return 0;
}

SDL_Surface *openOutput(int output, int width, int height) {
  SDL_Surface* screen;
  switch (output) {
    case 0: // SDL window
      screen = SDL_SetVideoMode(width, height, 32, SDL_RESIZABLE|SDL_SWSURFACE);  // Create a resizable window with SDL context
      if(screen)                                                    // if opened successful
      {
        fprintf(stderr, "open SDL window successful\n");
        return screen;                                              // return success
      } else {
        fprintf(stderr, "Cannot create SDL window > ");
        fprintf(stderr, SDL_GetError());
        fprintf(stderr, "\n");
        return 0;                                                   // return error
      }; break;
    case 1: // SDL fullscreen
      screen = SDL_SetVideoMode(width, height, 32, SDL_FULLSCREEN|SDL_SWSURFACE); // open a fullscreen-surface with SDL context
      if(screen)                                                    // if opened successful
      {
        SDL_WM_SetCaption("yDOOM", "yDOOM");                        // set the title ( that makes no sense )
        fprintf(stderr, "open SDL screen successful\n");
        return screen;                                              // return success
      } else {
        fprintf(stderr, "Cannot create SDL screen > ");
        fprintf(stderr, SDL_GetError());
        fprintf(stderr, "\n");
        return 0;                                                   // return error
      }; break;
    case 2: // FBdev
      fprintf(stderr, "Cannot create FBdev > not implimented yet\n");
      return 0;                                                     // return error
      break;
  };
  return 0;
}

SDL_Surface *resizeOutput(int output, int width, int height) {
  SDL_Surface* screen;
  switch (output) {
    case 0: // SDL window
      screen = SDL_SetVideoMode(width, height, 32, SDL_RESIZABLE|SDL_HWSURFACE);  // Recreate a resizable window with SDL context
      if(screen)                                                    // if opened successful
      {
        fprintf(stderr, "open SDL window successful\n");
        fprintf(stderr, "open SDL window successful\n");
        fprintf(stderr, "open SDL window successful\n");
        return screen;                                              // return success
      } else {
        fprintf(stderr, "Cannot create SDL window > ");
        fprintf(stderr, SDL_GetError());
        fprintf(stderr, "\n");
        return 0;                                                   // return error
      }; break;
    case 1: // SDL fullscreen
      return 0;
    case 2: // FBdev
      return 0;
  };
  return 0;
}

void setOutputTitle(int output, char title[]) {
  switch ( output ) {
    case 0: // SDL window
      SDL_WM_SetCaption(title, title);
      break;
  }
}


void plotPixel(int x, int y, Uint32 pixel) {
  Uint8 *p = (Uint8 *)render->pixels + y * render->pitch + x * 4;
  p[0] = (pixel >> 16) & 0xff;
  p[1] = (pixel >> 8) & 0xff;
  p[2] = pixel & 0xff;

}

void _plotPixel(int x, int y, Uint32 pixel) {
  if ( x >= 0 && x < width && y >= 0 && y < height ) {
    plotPixel(x,y,pixel);
  }
}

int startDrawing(int output, SDL_Surface *screen) {
  scale = height / 200;
  render = screen;
  if ( SDL_MUSTLOCK(screen) ) {
    if ( SDL_LockSurface(screen) < 0 ) {
      scale = 1;
      return 0;
    } else {
      return 1;
    }
  } else {
    return 1;
  }
}

int stopDrawing(int output, int final) {
  if ( SDL_MUSTLOCK(render) ) {
    SDL_UnlockSurface(render);
  }
  if ( final != 0 ) {
    SDL_UpdateRect(render, 0, 0, width, height);
  }
  return 1;
}

void outputStuff(int output) {
  if ( mouseLook != 0 ) {
    mouseLook = 0;
    fprintf(stderr, "mouselook are not supported yet\n");
  }
}
