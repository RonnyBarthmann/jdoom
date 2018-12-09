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

void updatePlayer(int delay, int x, int y, int a, int mx, int my, int s) {
  float d = (float) delay;
  if ( y == -1 && s != 0 ) {
    py -= sin(Radians(pa))*d/2;
    px -= cos(Radians(pa))*d/2;
  }
  if ( y == -1 && s == 0 ) {
    py -= sin(Radians(pa))*d/5;
    px -= cos(Radians(pa))*d/5;
  }
  if ( y == 1 && s != 0 ) {
    py += sin(Radians(pa))*d/2;
    px += cos(Radians(pa))*d/2;
  }
  if ( y == 1 && s == 0 ) {
    py += sin(Radians(pa))*d/5;
    px += cos(Radians(pa))*d/5;
  }
  if ( x == 1 && s != 0 ) {
    px -= sin(Radians(pa))*d/2;
    py += cos(Radians(pa))*d/2;
  }
  if ( x == 1 && s == 0 ) {
    px -= sin(Radians(pa))*d/5;
    py += cos(Radians(pa))*d/5;
  }
  if ( x == -1 && s != 0 ) {
    px += sin(Radians(pa))*d/2;
    py -= cos(Radians(pa))*d/2;
  }
  if ( x == -1 && s == 0 ) {
    px += sin(Radians(pa))*d/5;
    py -= cos(Radians(pa))*d/5;
  }
  if ( a == 1 ) {
    pa += d/10;
  }
  if ( a == -1 ) {
    pa -= d/10;
  }
}
