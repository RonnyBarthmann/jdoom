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

struct texture {
  int used;
  int width;
  int height;
  int *mem;
  int x;
  int y;
};
struct texture ImageMemory[255];

int DummyTex(int tex, int size, int c1, int c2) {
  fprintf(stderr, "Create Texture ... ");
  ImageMemory[tex].used = 0;                                 // set Text to "non-exist"
  ImageMemory[tex].mem = malloc(size * size * 4);            // try to allocate memory
  if ( ImageMemory[tex].mem == NULL ) {                      // if not success ...
    fprintf(stderr, "failed\n");
    return 0;                                                // ... break
  } else {                                                   // if success ...
    ImageMemory[tex].used = 1;                               // ... lock the textures ( set to "exist" )
    ImageMemory[tex].width = size;                           // store the size in x-dimension
    ImageMemory[tex].height = size;                          // and the size in y-dimension
    for ( int y = 0; y < size/2; y++) {
      for ( int x = 0; x < size/2 ; x++) {
        int *address = ImageMemory[tex].mem;
        *(address + ( ImageMemory[tex].width * y ) + x ) = c1;
      }
    }
    for ( int y = size/2; y < size; y++) {                   // draw lines from up to down
      for ( int x = size/2; x < size ; x++) {                // and the lines from left to right
        int *address = ImageMemory[tex].mem;                 // grab the address of the Texture-Memory
        *(address + ( ImageMemory[tex].width * y ) + x ) = c1;
      }
    }
    for ( int y = 0; y < size/2; y++) {
      for ( int x = size/2; x < size ; x++) {
        int *address = ImageMemory[tex].mem;
        *(address + ( ImageMemory[tex].width * y ) + x ) = c2;
      }
    }
    for ( int y = size/2; y < size; y++) {
      for ( int x = 0; x < size/2 ; x++) {
        int *address = ImageMemory[tex].mem;
        *(address + ( ImageMemory[tex].width * y ) + x ) = c2;
      }
    }
    ImageMemory[tex].x = size/2;                             // store the x-cordinate of the center ( grab point )
    ImageMemory[tex].y = size;                               // store the y-cordinate of the center
    fprintf(stderr, "done\n");
    return 1;
  }
};

int getTexPixel(int tex, int x, int y, double rot) {
  if ( ImageMemory[tex].used == 1 ) {
    x += 1000000000; // workaround for Modula
    y += 1000000000; // workaround for Module
    x %= ImageMemory[tex].width;  // map the x pointer into the Texture
    y %= ImageMemory[tex].height; // map the y pointer into the Texture
    if ( rot != 0 ) {
      fprintf(stderr, "warning : Rotation is not god implimented\n");
      double xt = x;
      double yt = y;
      x = (xt*cos(Radians(rot)))-(yt*sin(Radians(rot)));
      y = (xt*sin(Radians(rot)))+(yt*cos(Radians(rot)));
      x += 1000000000; // workaround for Modula
      y += 1000000000; // workaround for Module
      x %= ImageMemory[tex].width;  // map the x pointer into the Texture
      y %= ImageMemory[tex].height; // map the y pointer into the Texture
    }
    return *(ImageMemory[tex].mem+(y*ImageMemory[tex].width*4)+(x*4));
  }
}

int getTexWigth(int tex) { return ImageMemory[tex].width; };
int getTexHeight(int tex) { return ImageMemory[tex].height; };
int getTexX(int tex) { return ImageMemory[tex].x; };
int getTexY(int tex) { return ImageMemory[tex].y; };

