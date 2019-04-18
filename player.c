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

void DrawFlatPOV(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double z, int tex) {
  double ox1, oy1, ox2, oy2, ox3, oy3, ox4, oy4;
  x1 -= px;
  y1 -= py;
  x2 -= px;
  y2 -= py;
  x3 -= px;
  y3 -= py;
  x4 -= px;
  y4 -= py;

  ox1 = 0 + ( x1 * cos(0-pa) ) - ( y1 * sin(0-pa) );
  oy1 = 0 + ( y1 * cos(0-pa) ) + ( x1 * sin(0-pa) );
  ox2 = 0 + ( x2 * cos(0-pa) ) - ( y2 * sin(0-pa) );
  oy2 = 0 + ( y2 * cos(0-pa) ) + ( x2 * sin(0-pa) );
  ox3 = 0 + ( x3 * cos(0-pa) ) - ( y3 * sin(0-pa) );
  oy3 = 0 + ( y3 * cos(0-pa) ) + ( x3 * sin(0-pa) );
  ox4 = 0 + ( x4 * cos(0-pa) ) - ( y4 * sin(0-pa) );
  oy4 = 0 + ( y4 * cos(0-pa) ) + ( x4 * sin(0-pa) );

  DrawFlat(ox1,oy1,ox2,oy2,ox3,oy3,ox4,oy4,z,tex);
}

void DrawCellingPOV(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double z, int tex) {
  double ox1, oy1, ox2, oy2, ox3, oy3, ox4, oy4;
  x1 -= px;
  y1 -= py;
  x2 -= px;
  y2 -= py;
  x3 -= px;
  y3 -= py;
  x4 -= px;
  y4 -= py;

  ox1 = 0 + ( x1 * cos(0-pa) ) - ( y1 * sin(0-pa) );
  oy1 = 0 + ( y1 * cos(0-pa) ) + ( x1 * sin(0-pa) );
  ox2 = 0 + ( x2 * cos(0-pa) ) - ( y2 * sin(0-pa) );
  oy2 = 0 + ( y2 * cos(0-pa) ) + ( x2 * sin(0-pa) );
  ox3 = 0 + ( x3 * cos(0-pa) ) - ( y3 * sin(0-pa) );
  oy3 = 0 + ( y3 * cos(0-pa) ) + ( x3 * sin(0-pa) );
  ox4 = 0 + ( x4 * cos(0-pa) ) - ( y4 * sin(0-pa) );
  oy4 = 0 + ( y4 * cos(0-pa) ) + ( x4 * sin(0-pa) );

  DrawCelling(ox1,oy1,ox2,oy2,ox3,oy3,ox4,oy4,z,tex);
}

void DrawWallPOV(double x1, double y1, double x2, double y2, double z, double h, int tex) {
  double ox1, oy1, ox2, oy2;
  x1 -= px;
  y1 -= py;
  x2 -= px;
  y2 -= py;

  ox1 = 0 + ( x1 * cos(0-pa) ) - ( y1 * sin(0-pa) );
  oy1 = 0 + ( y1 * cos(0-pa) ) + ( x1 * sin(0-pa) );
  ox2 = 0 + ( x2 * cos(0-pa) ) - ( y2 * sin(0-pa) );
  oy2 = 0 + ( y2 * cos(0-pa) ) + ( x2 * sin(0-pa) );

  DrawWall(ox1,oy1,ox2,oy2,z,h,tex);
}

void DrawSpritePOV(double x, double y, double z, int tex, int rot) {
  double ox, oy;
  x -= px;
  y -= py;

  ox = 0 + ( x * cos(0-pa) ) - ( y * sin(0-pa) );
  oy = 0 + ( y * cos(0-pa) ) + ( x * sin(0-pa) );

  DrawSprite(ox,oy,z,tex,rot);
}

int IfLineVisPOV(double x1, double y1, double x2, double y2) {
  double ox1, oy1, ox2, oy2;
  x1 -= px;
  y1 -= py;
  x2 -= px;
  y2 -= py;

  ox1 = 0 + ( x1 * cos(0-pa) ) - ( y1 * sin(0-pa) );
  oy1 = 0 + ( y1 * cos(0-pa) ) + ( x1 * sin(0-pa) );
  ox2 = 0 + ( x2 * cos(0-pa) ) - ( y2 * sin(0-pa) );
  oy2 = 0 + ( y2 * cos(0-pa) ) + ( x2 * sin(0-pa) );

  return ifLineVis(ox1,oy1,ox2,oy2);
}

void updatePlayer(int delay, int x, int y, int a, int mx, int my, int s) {
  float d = (float) delay;
  if ( x == -1 && s != 0 ) {
    py -= sin(pa)*d/2;
    px -= cos(pa)*d/2;
  }
  if ( x == -1 && s == 0 ) {
    py -= sin(pa)*d/5;
    px -= cos(pa)*d/5;
  }
  if ( x == 1 && s != 0 ) {
    py += sin(pa)*d/2;
    px += cos(pa)*d/2;
  }
  if ( x == 1 && s == 0 ) {
    py += sin(pa)*d/5;
    px += cos(pa)*d/5;
  }
  if ( y == 1 && s != 0 ) {
    px -= sin(pa)*d/2;
    py += cos(pa)*d/2;
  }
  if ( y == 1 && s == 0 ) {
    px -= sin(pa)*d/5;
    py += cos(pa)*d/5;
  }
  if ( y == -1 && s != 0 ) {
    px += sin(pa)*d/2;
    py -= cos(pa)*d/2;
  }
  if ( y == -1 && s == 0 ) {
    px += sin(pa)*d/5;
    py -= cos(pa)*d/5;
  }
  if ( a == 1 ) {
    pa += d/1000;
  }
  if ( a == -1 ) {
    pa -= d/1000;
  }
}
