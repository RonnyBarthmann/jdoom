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

// Mainoptions
int    width = 800;      // window or screen width
int    height = 600;     // window or screen height
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

// Konstanten ( Limits )
#define MAX_SECTORS 1024  // Maximum of sectors that can be handled from the engine
