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

#include "map.h"

struct wl {                                   // Structure of a single Wall
  int id;                                     // ID of the Wall
  double leftP, rightP, upperP, lowerP;       // Percent how much the side comes into the wall
  int leftTex, rightTex, upperTex, lowerTex;  // Texture used by the side of wall
};

struct rd {                                           // Structure of a single Sector
  double x1, y1, x2, y2, x3, y3, x4, y4;              // Coordinates of the edges from the sector
  double groundY, height;                             // Vertical position and height of the sector
  struct wl front, right, back, left, cover, ground;  // Infos about the side-walls from the sector ... see above
};

struct rd RoomData[MAX_SECTORS];
int RoomDraw[MAX_SECTORS];
int Rooms;

int InitIWAD(char name[]) {
  if ( name == "" ) {
    fprintf(stderr, "no IWAD was specified\n");
    return 0;
  } else {
    iwad = ini_load(name);
    if ( iwad == NULL ) {
      fprintf(stderr, "Cannot load IWAD %s\n", name);
      return 0;
    } else {
      if ( ini_get(iwad, NULL, "type") == "IWAD" ) {
        fprintf(stderr, "Used IWAD %s is not Supported, please use v2 IWads only \n", name);
        return 1;
      } else if ( ini_get(iwad, NULL, "type") == "IWADv2" ) {
        fprintf(stderr, "Using IWAD %s\n", name);
        return 1;
      } else {
        fprintf(stderr, "Cannot load IWAD %s\n", name);
        return 0;
      }
    }
  }
  return 0;
};

int LoadMap(char name[]) {
  int i;
  const char *room;
  const char *tmp;
  if ( ini_get(iwad, name, "StartX") == NULL ) {
    fprintf(stderr, "Cannot find map %s\n", name);
    return 0;
  }
  tmp = ini_get(iwad, name, "StartX");
  if ( tmp == NULL ) {
    fprintf(stderr, "Map: %s - Cannot find player StartX\n", name);
    return 0;
  }
  px = atof(tmp);
  tmp = ini_get(iwad, name, "StartY");
  if ( tmp == NULL ) {
    fprintf(stderr, "Map: %s - Cannot find player StartY\n", name);
    return 0;
  }
  py = atof(tmp);
  tmp = ini_get(iwad, name, "StartA");
  if ( tmp == NULL ) {
    fprintf(stderr, "Map: %s - Cannot find player StartA\n", name);
    return 0;
  }
  pa = atof(tmp);
  tmp = ini_get(iwad, name, "sectors");
  if ( tmp == NULL ) {
    fprintf(stderr, "Map: %s - Cannot find count of sectors\n", name);
    return 0;
  }
  Rooms = atoi(tmp);

  char sectorname[12];
  for (int i=0; i<Rooms; i++) {
    sprintf(sectorname,"sec%05d",i);
    room = ini_get(iwad, name, sectorname);
    if ( room == NULL ) {
      fprintf(stderr, "Map: %s - sector %s has no data\n", name, sectorname);
      return 0;
    }

    // sector geometry ( fild 1 - 10 )
    RoomData[i].x1 = atof(strtok(strdup(room),","));
    RoomData[i].y1 = atof(strtok(NULL,","));
    RoomData[i].x2 = atof(strtok(NULL,","));
    RoomData[i].y2 = atof(strtok(NULL,","));
    RoomData[i].x3 = atof(strtok(NULL,","));
    RoomData[i].y3 = atof(strtok(NULL,","));
    RoomData[i].x4 = atof(strtok(NULL,","));
    RoomData[i].y4 = atof(strtok(NULL,","));
    RoomData[i].groundY = atof(strtok(NULL,","));
    RoomData[i].height = atof(strtok(NULL,","));

    // informations about faced wall ( field 11 - 19 )
    RoomData[i].front.id = atoi(strtok(NULL,","));
    RoomData[i].front.leftP = atof(strtok(NULL,","));
    RoomData[i].front.rightP = atof(strtok(NULL,","));
    RoomData[i].front.upperP = atof(strtok(NULL,","));
    RoomData[i].front.lowerP = atof(strtok(NULL,","));
    RoomData[i].front.leftTex = atoi(strtok(NULL,","));
    RoomData[i].front.rightTex = atoi(strtok(NULL,","));
    RoomData[i].front.upperTex = atoi(strtok(NULL,","));
    RoomData[i].front.lowerTex = atoi(strtok(NULL,","));

    // informations about  wall ( field 20 - 28 )
    RoomData[i].right.id = atoi(strtok(NULL,","));
    RoomData[i].right.leftP = atof(strtok(NULL,","));
    RoomData[i].right.rightP = atof(strtok(NULL,","));
    RoomData[i].right.upperP = atof(strtok(NULL,","));
    RoomData[i].right.lowerP = atof(strtok(NULL,","));
    RoomData[i].right.leftTex = atoi(strtok(NULL,","));
    RoomData[i].right.rightTex = atoi(strtok(NULL,","));
    RoomData[i].right.upperTex = atoi(strtok(NULL,","));
    RoomData[i].right.lowerTex = atoi(strtok(NULL,","));

    // informations about  wall ( field 29 - 37 )
    RoomData[i].back.id = atoi(strtok(NULL,","));
    RoomData[i].back.leftP = atof(strtok(NULL,","));
    RoomData[i].back.rightP = atof(strtok(NULL,","));
    RoomData[i].back.upperP = atof(strtok(NULL,","));
    RoomData[i].back.lowerP = atof(strtok(NULL,","));
    RoomData[i].back.leftTex = atoi(strtok(NULL,","));
    RoomData[i].back.rightTex = atoi(strtok(NULL,","));
    RoomData[i].back.upperTex = atoi(strtok(NULL,","));
    RoomData[i].back.lowerTex = atoi(strtok(NULL,","));

    // informations about  wall ( field 38 - 46 )
    RoomData[i].left.id = atoi(strtok(NULL,","));
    RoomData[i].left.leftP = atof(strtok(NULL,","));
    RoomData[i].left.rightP = atof(strtok(NULL,","));
    RoomData[i].left.upperP = atof(strtok(NULL,","));
    RoomData[i].left.lowerP = atof(strtok(NULL,","));
    RoomData[i].left.leftTex = atoi(strtok(NULL,","));
    RoomData[i].left.rightTex = atoi(strtok(NULL,","));
    RoomData[i].left.upperTex = atoi(strtok(NULL,","));
    RoomData[i].left.lowerTex = atoi(strtok(NULL,","));

    // informations about  wall ( field 47 - 55 )
    RoomData[i].cover.id = atoi(strtok(NULL,","));
    RoomData[i].cover.leftP = atof(strtok(NULL,","));
    RoomData[i].cover.rightP = atof(strtok(NULL,","));
    RoomData[i].cover.upperP = atof(strtok(NULL,","));
    RoomData[i].cover.lowerP = atof(strtok(NULL,","));
    RoomData[i].cover.leftTex = atoi(strtok(NULL,","));
    RoomData[i].cover.rightTex = atoi(strtok(NULL,","));
    RoomData[i].cover.upperTex = atoi(strtok(NULL,","));
    RoomData[i].cover.lowerTex = atoi(strtok(NULL,","));

    // informations about  wall ( field 56 - 64 )
    RoomData[i].ground.id = atoi(strtok(NULL,","));
    RoomData[i].ground.leftP = atof(strtok(NULL,","));
    RoomData[i].ground.rightP = atof(strtok(NULL,","));
    RoomData[i].ground.upperP = atof(strtok(NULL,","));
    RoomData[i].ground.lowerP = atof(strtok(NULL,","));
    RoomData[i].ground.leftTex = atoi(strtok(NULL,","));
    RoomData[i].ground.rightTex = atoi(strtok(NULL,","));
    RoomData[i].ground.upperTex = atoi(strtok(NULL,","));
    RoomData[i].ground.lowerTex = atoi(strtok(NULL,","));
  }

  fprintf(stderr, "Map %s successfully loaded\n", name);
  return 1;
}

int getNearestRoom(int init) {
  int room=init;
  double dist=DBL_MAX, a, b, c;
  for (int i=init; i<Rooms; i++) {
    a = RoomData[i].x1;
    b = RoomData[i].y1;
    a += RoomData[i].x2;
    b += RoomData[i].y2;
    a += RoomData[i].x3;
    b += RoomData[i].y3;
    a += RoomData[i].x4;
    b += RoomData[i].y4;
    a/=4;
    b/=4;
    a = round(a-px);
    b = round(b-py);
    c = sqrt((a*a)+(b*b));
    if ( c < dist ) {
      room = i;
      dist = c;
    }
  }
  return room;
}

void _DrawRoomSide(double x1,double y1,double x2,double y2,double z,double h,double left,double right,double upper,double lower,int leTex,int riTex,int upTex,int loTex) {
  double tempX, tempY, tempH;
  if ( left >= 100 ) {
    DrawWallPOV(x1,y1,x2,y2,z,h,leTex);
    return;
  } else if ( left > 0 ) {
    tempX = ((x1*(100-left))+(x2*left))/100;
    tempY = ((y1*(100-left))+(y2*left))/100;
    DrawWallPOV(x1,y1,tempX,tempY,z,h,leTex);
    x1 = tempX;
    y1 = tempY;
  }
  if ( right >= 100 ) {
    DrawWallPOV(x1,y1,x2,y2,z,h,riTex);
    return;
  } else if ( right > 0 ) {
    tempX = ((x1*right)+(x2*(100-right)))/100;
    tempY = ((y1*right)+(y2*(100-right)))/100;
    DrawWallPOV(tempX,tempY,x2,y2,z,h,riTex);
    x2 = tempX;
    y2 = tempY;
  }
  if ( upper >= 100 ) {
    DrawWallPOV(x1,y1,x2,y2,z,h,upTex);
    return;
  } else if ( upper > 0 ) {
    tempH = (h*upper)/100;
    DrawWallPOV(x1,y1,x2,y2,z-h+tempH,tempH,upTex);
    h - tempH;
  }
  if ( lower >= 100 ) {
    DrawWallPOV(x1,y1,x2,y2,z,h,loTex);
    return;
  } else if ( lower > 0 ) {
    h = (h*lower)/100;
    DrawWallPOV(x1,y1,x2,y2,z,h,loTex);
  }
}

void _DrawRoom(int room) {
  DrawFlatPOV(RoomData[room].x1,RoomData[room].y1,RoomData[room].x2,RoomData[room].y2,RoomData[room].x3,RoomData[room].y3,RoomData[room].x4,RoomData[room].y4,RoomData[room].groundY,RoomData[room].ground.leftTex);
  DrawCellingPOV(RoomData[room].x1,RoomData[room].y1,RoomData[room].x2,RoomData[room].y2,RoomData[room].x3,RoomData[room].y3,RoomData[room].x4,RoomData[room].y4,RoomData[room].groundY-RoomData[room].height,RoomData[room].cover.leftTex);
  if ( RoomData[room].back.id >= 0 ) {
    _DrawRoomSide(RoomData[room].x1,RoomData[room].y1,RoomData[room].x2,RoomData[room].y2,RoomData[room].groundY,RoomData[room].height,RoomData[room].back.leftP,RoomData[room].back.rightP,RoomData[room].back.upperP,RoomData[room].back.lowerP,RoomData[room].back.leftTex,RoomData[room].back.rightTex,RoomData[room].back.upperTex,RoomData[room].back.lowerTex);
  } else {
    DrawWallPOV(RoomData[room].x1,RoomData[room].y1,RoomData[room].x2,RoomData[room].y2,RoomData[room].groundY,RoomData[room].height,RoomData[room].back.leftTex);
  }
  if ( RoomData[room].right.id >= 0 ) {
    _DrawRoomSide(RoomData[room].x2,RoomData[room].y2,RoomData[room].x3,RoomData[room].y3,RoomData[room].groundY,RoomData[room].height,RoomData[room].right.leftP,RoomData[room].right.rightP,RoomData[room].right.upperP,RoomData[room].right.lowerP,RoomData[room].right.leftTex,RoomData[room].right.rightTex,RoomData[room].right.upperTex,RoomData[room].right.lowerTex);
  } else {
    DrawWallPOV(RoomData[room].x2,RoomData[room].y2,RoomData[room].x3,RoomData[room].y3,RoomData[room].groundY,RoomData[room].height,RoomData[room].right.leftTex);
  }
  if ( RoomData[room].front.id >= 0 ) {
    _DrawRoomSide(RoomData[room].x3,RoomData[room].y3,RoomData[room].x4,RoomData[room].y4,RoomData[room].groundY,RoomData[room].height,RoomData[room].front.leftP,RoomData[room].front.rightP,RoomData[room].front.upperP,RoomData[room].front.lowerP,RoomData[room].front.leftTex,RoomData[room].front.rightTex,RoomData[room].front.upperTex,RoomData[room].front.lowerTex);
  } else {
    DrawWallPOV(RoomData[room].x3,RoomData[room].y3,RoomData[room].x4,RoomData[room].y4,RoomData[room].groundY,RoomData[room].height,RoomData[room].front.leftTex);
  }
  if ( RoomData[room].left.id >= 0 ) {
    _DrawRoomSide(RoomData[room].x4,RoomData[room].y4,RoomData[room].x1,RoomData[room].y1,RoomData[room].groundY,RoomData[room].height,RoomData[room].left.leftP,RoomData[room].left.rightP,RoomData[room].left.upperP,RoomData[room].left.lowerP,RoomData[room].left.leftTex,RoomData[room].left.rightTex,RoomData[room].left.upperTex,RoomData[room].left.lowerTex);
  } else {
    DrawWallPOV(RoomData[room].x4,RoomData[room].y4,RoomData[room].x1,RoomData[room].y1,RoomData[room].groundY,RoomData[room].height,RoomData[room].left.leftTex);
  }
}

void DrawRoom(int room) {
  RoomDraw[room] = 0;
  if ( IfLineVisPOV(RoomData[room].x1,RoomData[room].y1,RoomData[room].x2,RoomData[room].y2) != 0 ) {
    if ( RoomDraw[RoomData[room].back.id] >= 0 ) {
      DrawRoom(RoomData[room].back.id);
    }
  }
  if ( IfLineVisPOV(RoomData[room].x2,RoomData[room].y2,RoomData[room].x3,RoomData[room].y3) != 0 ) {
    if ( RoomDraw[RoomData[room].right.id] >= 0 ) {
      DrawRoom(RoomData[room].right.id);
    }
  }
  if ( IfLineVisPOV(RoomData[room].x3,RoomData[room].y3,RoomData[room].x4,RoomData[room].y4) != 0 ) {
    if ( RoomDraw[RoomData[room].front.id] >= 0 ) {
      DrawRoom(RoomData[room].front.id);
    }
  }
  if ( IfLineVisPOV(RoomData[room].x4,RoomData[room].y4,RoomData[room].x1,RoomData[room].y1) != 0 ) {
    if ( RoomDraw[RoomData[room].left.id] >= 0 ) {
      DrawRoom(RoomData[room].left.id);
    }
  }
  _DrawRoom(room);
}

int DrawRooms(int start) {
  for (int i=0; i<MAX_SECTORS; i++) {
    RoomDraw[i] = 1;
  }
  if ( start < Rooms ) {
    DrawRoom(start);
    return 1;
  } else {
    fprintf(stderr, "POV-sector %d dos not exist\n", start);
    return 0;
  }
  return 0;
}

