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



//   original ----------------------------------------------------------



void clearScene() {
  for ( int y = 0; y < height; y++ ) {
    for ( int x = 0; x < width; x++ ) {
      zBuffer[x][y] = 16777216;
      plotPixel(x,y,0);
    }
  }
}

void _DrawLineX(int x1, int x2, int y, double z, int cell, int tex) {
  double tx, ty;
  int i;
  if ( x1 < 0 ) x1 = 0;
  if ( x2 >= width ) x2 = width-1;
  if ( x1 > x2 ) {
    x1 -= x2;
    x2 += x1;
    x1 = x2 - x1;
  }
  if ( y < 0 ) return;
  if ( y >= height ) return;
  if ( RenderFlatTex != 0 ) {
    if ( cell != 0 ) {
      for ( i = x1; i <= x2; i++ ) {
        if ( i >= 0 && i < width ) {
          ty = getCeiling3Dy(width,height,i,y,z,0);
          if ( zBuffer[i][y] > ty ) {
            zBuffer[i][y] = ty;
            tx = getCeiling3Dx(width,height,i,y,z,ty);
            plotPixel(i,y,getTexPixel(tex,tx,ty,0)) ;
          }
        }
      }
    } else {
      for ( i = x1; i <= x2; i++ ) {
        if ( i >= 0 && i < width ) {
          ty = getFlat3Dy(width,height,i,y,z,0);
          if ( zBuffer[i][y] > ty ) {
            zBuffer[i][y] = ty;
            tx = getFlat3Dx(width,height,i,y,z,ty);
            plotPixel(i,y,getTexPixel(tex,tx,ty,0));
          }
        }
      }
    }
  } else {
    tex = getTexPixel(tex,0,0,0);
    if ( cell != 0 ) {
      for ( i = x1; i <= x2; i++ ) {
        if ( i >= 0 && i < width ) {
          ty = getCeiling3Dy(width,height,i,y,z,0);
          if ( zBuffer[i][y] > ty ) {
            zBuffer[i][y] = ty;
            plotPixel(i,y,tex);
          }
        }
      }
    } else {
      for ( i = x1; i <= x2; i++ ) {
        if ( i >= 0 && i < width ) {
          ty = getFlat3Dy(width,height,i,y,z,0);
          if ( zBuffer[i][y] > ty ) {
            zBuffer[i][y] = ty;
            plotPixel(i,y,tex);
          }
        }
      }
    }
  }
}

void _DrawLineY(int x, int y1, int y2, double d, double tx, double h, int tex) {
  double ty, yTexStep;
  int i, c;
  if ( y1 < 0 ) y1 = 0;
  if ( y2 >= height ) y2 = height-1;
  if ( y1 > y2 ) return;
  if ( x < 0 ) return;
  if ( x >= height ) return;
  yTexStep = h / ( y2 - y1 );
  if ( RenderWallTex != 0 ) {
    for ( i = y1; i <= y2; i++ ) {
      if ( i >= 0 && i < height ) {
        if ( zBuffer[x][i] > d ) {
          zBuffer[x][i] = d;
          plotPixel(x,i,getTexPixel(tex,tx,ty,0));
        }
        ty += yTexStep;
      }
    }
  } else {
    tex = getTexPixel(tex,0,0,0);
    for ( i = y1; i <= y2; i++ ) {
      if ( i >= 0 && i < height ) {
        if ( zBuffer[x][i] > d ) {
          zBuffer[x][i] = d;
          plotPixel(x,i,tex);
        }
        ty += yTexStep;
      }
    }
  }
}

void LineXY(int x1, int y1, int x2, int y2, int c) {
  if ( x1 > x2 ) {
    x1 -= x2;
    x2 += x1;
    x1 = x2 - x1;
    y1 -= y2;
    y2 += y1;
    y1 = y2 - y1;
  }
  double dx = x2 - x1;
  double dy = y2 - y1;
  double s = dy / dx;
  double y = y1;
  for ( int x = x1; x <= x2; x++ ) {
    _plotPixel(x,y,c);
    y += s;
  }
}

void Line(int x, int y, int w, int h, int c) {
  fprintf(stderr,"render.c > Line() ist not implimented\n");
  // zBuffer = 0
}

void Box(int x, int y, int w, int h, int c) {
  fprintf(stderr,"render.c > Box() ist not implimented\n");
  // zBuffer = 0
}

void _DrawFlat2(double x1, double y1, double x2, double y2, double x3, double y3, double z, int tex, int cell) {
  double aLeftStep, aRightStep, vLeftStep, vRightStep;
  int aTriHeight, vTriHeight;
  int TriMode, i, ox4, oy4, oy, behindCam=0;
  double ox1, oy1, ox2, oy2, ox3, oy3, oxL, oxR;
  if ( y1 > 0 ) {
    ox1 = ( ( x1 * ( height / 2 ) ) / y1 ) + ( width / 2 );
    oy1 = ( ( z * ( height / 2 ) ) / y1 ) + ( height / 2 );
  } else {
    behindCam = 1;
  }
  if ( y2 > 0 ) {
    ox2 = ( ( x2 * ( height / 2 ) ) / y2 ) + ( width / 2 );
    oy2 = ( ( z * ( height / 2 ) ) / y2 ) + ( height / 2 );
  } else {
    behindCam = 1;
  }
  if ( y3 > 0 ) {
    ox3 = ( ( x3 * ( height / 2 ) ) / y3 ) + ( width / 2 );
    oy3 = ( ( z * ( height / 2 ) ) / y3 ) + ( height / 2 );
  } else {
    behindCam = 1;
  }
  if ( DebugModeFlat != 0 ) {
    if ( y1 > 0 && y2 > 0 ) {
      LineXY(ox1,oy1,ox2,oy2,255);
    }
    if ( y2 > 0 && y3 > 0 ) {
      LineXY(ox2,oy2,ox3,oy3,255);
    }
    if ( y3 > 0 && y1 > 0 ) {
      LineXY(ox3,oy3,ox1,oy1,255);
    }
    if ( y1 > 0 ) {
      Box(ox1-2,oy1-2,5,5,255);
    }
    if ( y2 > 0 ) {
      Box(ox2-2,oy2-2,5,5,255);
    }
    if ( y3 > 0 ) {
      Box(ox3-2,oy3-2,5,5,255);
    }
  }
  if ( behindCam != 0 ) return;
  if ( oy1 > oy2 ) {
    ox1 -= ox2;
    ox2 += ox1;
    ox1 = ox2 - ox1;
    oy1 -= oy2;
    oy2 += oy1;
    oy1 = oy2 - oy1;
  }
  if ( oy1 > oy3 ) {
    ox1 -= ox3;
    ox3 += ox1;
    ox1 = ox3 - ox1;
    oy1 -= oy3;
    oy3 += oy1;
    oy1 = oy3 - oy1;
  }
  if ( oy2 > oy3 ) {
    ox2 -= ox3;
    ox3 += ox2;
    ox2 = ox3 - ox2;
    oy2 -= oy3;
    oy3 += oy2;
    oy2 = oy3 - oy2;
  }
  if ( oy1 == oy3 ) {
    TriMode = 3;     // Line  -
    if ( ox1 > ox2 ) {
      ox1 -= ox2;
      ox2 += ox1;
      ox1 = ox2 - ox1;
    }
    if ( ox1 > ox3 ) {
      ox1 -= ox3;
      ox3 += ox1;
      ox1 = ox3 - ox1;
    }
    if ( ox2 > ox3 ) {
      ox2 -= ox3;
      ox3 += ox2;
      ox2 = ox3 - ox2;
    }
  } else if ( oy1 == oy2 ) {
    TriMode = 2;     // Down  V
    if ( ox1 > ox2 ) {
      ox1 -= ox2;
      ox2 += ox1;
      ox1 = ox2 - ox1;
    }
  } else if ( oy2 == oy3 ) {
    TriMode = 1;     // Up    A
    if ( ox2 > ox3 ) {
      ox2 -= ox3;
      ox3 += ox2;
      ox2 = ox3 - ox2;
    }
  } else {
    TriMode = 0;     // Side  < or >
  }
  switch ( TriMode ) {
    case 0:   // Side  < or >
      i = oy3 - oy1;
      aTriHeight = oy2 - oy1;
      vTriHeight = oy3 - oy2;
      ox4 = ((ox1*vTriHeight)+(ox3*aTriHeight)) / i;
      oy4 = oy2;

      aTriHeight = oy2 - oy1;
      aLeftStep = (ox2-ox1)/aTriHeight;
      aRightStep = (ox4-ox1)/aTriHeight;
      oxL = ox1;
      oxR = ox1;
      for ( i = oy1; i <= oy2; i++ ) {
        _DrawLineX(oxL,oxR,i,z,cell,tex);
        oxL += aLeftStep;
        oxR += aRightStep;
      }
      vTriHeight = oy3 - oy2;
      vLeftStep = (ox3-ox2)/vTriHeight;
      vRightStep = (ox3-ox4)/vTriHeight;
      oxL = ox2;
      oxR = ox4;
      for ( i = oy2; i <= oy3; i++ ) {
        _DrawLineX(oxL,oxR,i,z,cell,tex);
        oxL += vLeftStep;
        oxR += vRightStep;
      }
      break;
    case 1:   // Up    A
      aTriHeight = oy2 - oy1;
      aLeftStep = (ox2-ox1)/aTriHeight;
      aRightStep = (ox3-ox1)/aTriHeight;
      oxL = ox1;
      oxR = ox1;
      for ( i = oy1; i <= oy2; i++ ) {
        _DrawLineX(oxL,oxR,i,z,cell,tex);
        oxL += aLeftStep;
        oxR += aRightStep;
      }
      break;
    case 2:   // Down  V
      vTriHeight = oy3 - oy1;
      vLeftStep = (ox3-ox1)/vTriHeight;
      vRightStep = (ox3-ox2)/vTriHeight;
      oxL = ox1;
      oxR = ox2;
      for ( i = oy1; i <= oy3; i++ ) {
        _DrawLineX(oxL,oxR,i,z,cell,tex);
        oxL += vLeftStep;
        oxR += vRightStep;
      }
      break;
    case 3:   // Line  -
      break;
  }
  if ( DebugModeFlat != 0 ) {
    if ( y1 > 0 && y2 > 0 ) {
      LineXY(ox1,oy1,ox2,oy2,255);
    }
    if ( y2 > 0 && y3 > 0 ) {
      LineXY(ox2,oy2,ox3,oy3,255);
    }
    if ( y3 > 0 && y1 > 0 ) {
      LineXY(ox3,oy3,ox1,oy1,255);
    }
    if ( y1 > 0 ) {
      Box(ox1-2,oy1-2,5,5,255);
    }
    if ( y2 > 0 ) {
      Box(ox2-2,oy2-2,5,5,255);
    }
    if ( y3 > 0 ) {
      Box(ox3-2,oy3-2,5,5,255);
    }
  }
}

int ifLineVis(double x1, double y1, double x2, double y2) {
  double ox1, ox2, y1end=0, y2end=0;
  if ( y1 > 0 ) {
    ox1 = ( ( x1 * ( height / 2 ) ) / y1 ) + ( width / 2 );
  } else {
    y1end = 1;
  }
  if ( y2 > 0 ) {
    ox2 = ( ( x2 * ( height / 2 ) ) / y2 ) + ( width / 2 );
  } else {
    y2end = 1;
  }
  if ( y1end+y2end == 0 ) {
    if ( ox2 > ox1 ) {
      if ( ox2 > 0 ) {
        if ( ox1 < width ) {
          return 1;
        }
      }
    }
  } else if ( y1end+y2end == 1 ) {
    if ( y1end == 0 ) {
      if ( ox1 < width ) {
        return 1;
      }
    } else if ( y2end == 0 ) {
      if ( ox2 > 0 ) {
        return 1;
      }
    }
  }
  return 0;
}

void _DrawWall2(double x1, double y1, double x2, double y2, double z, double h, int tex) {
  double ox1, oy1, oh1, ox2, oy2, oh2, yWallStep, hWallStep, dWallStep, xTexStep, oy, oh, od, tx;
  int i, reverse;
  ox1 = ( ( x1 * ( height / 2 ) ) / y1 ) + ( width / 2 );
  oy1 = ( ( z * ( height / 2 ) ) / y1 ) + ( height / 2 );
  oh1 =   ( h * ( height / 2 ) ) / y1;
  ox2 = ( ( x2 * ( height / 2 ) ) / y2 ) + ( width / 2 );
  oy2 = ( ( z * ( height / 2 ) ) / y2 ) + ( height / 2 );
  oh2 =   ( h * ( height / 2 ) ) / y2;
  if ( DebugModeWall != 0 ) {
    if ( y1 > 0 ) {
      Box(ox1-2,oy1-2,5,5,255);
      Box(ox1-2,oy1-oh1-2,5,5,255);
      Line(ox1,oy1,1,-oh1,255);
    }
    if ( y2 > 0 ) {
      Box(ox2-2,oy2-2,5,5,255);
      Box(ox2-2,oy2-oh2-2,5,5,255);
      Line(ox2,oy2,1,-oh2,255);
    }
    if ( y1 > 0 && y2 > 0 ) {
      LineXY(ox1,oy1,ox2,oy2,255);
      LineXY(ox1,oy1-oh1,ox2,oy2-oh2,255);
    }
  }
  if ( ox1 == ox2 ) return;
  reverse = 0;
  if ( ox1 > ox2 ) {
    ox1 -= ox2;
    ox2 += ox1;
    ox1 = ox2 - ox1;
    oy1 -= oy2;
    oy2 += oy1;
    oy1 = oy2 - oy1;
    oh1 -= oh2;
    oh2 += oh1;
    oh1 = oh2 - oh1;
    reverse = 1;
    return; // Draw only one side
  }
  yWallStep = ( oy2 - oy1 ) / ( ox2 - ox1 );
  hWallStep = ( oh2 - oh1 ) / ( ox2 - ox1 );
  dWallStep = ( y2 - y1 ) / ( ox2 - ox1 );
  oy = oy1;
  oh = oh1;
  od = y1;
  if ( reverse != 0 ) {
    xTexStep = 0 - ( sqrt( ( ( x1 - x2 ) * ( x1 - x2 ) ) + ( ( y1 - y2 ) * ( y1 - y2 ) ) ) / ( ox2 - ox1 ) );
    tx = sqrt( ( ( x1 - x2 ) * ( x1 - x2 ) ) + ( ( y1 - y2 ) * ( y1 - y2 ) ) );
  } else {
    xTexStep = sqrt( ( ( x1 - x2 ) * ( x1 - x2 ) ) + ( ( y1 - y2 ) * ( y1 - y2 ) ) ) / ( ox2 - ox1 );
    tx = 0;
  }
  for ( i = ox1; i <= ox2; i++ ) {
    _DrawLineY(i,oy-oh,oy,od,tx,h,tex);
    oy += yWallStep;
    oh += hWallStep;
    od += dWallStep;
    tx += xTexStep;
  }
  if ( DebugModeWall != 0 ) {
    if ( y1 > 0 ) {
      Box(ox1-2,oy1-2,5,5,255);
      Box(ox1-2,oy1-oh1-2,5,5,255);
      Line(ox1,oy1,1,-oh1,255);
    }
    if ( y2 > 0 ) {
      Box(ox2-2,oy2-2,5,5,255);
      Box(ox2-2,oy2-oh2-2,5,5,255);
      Line(ox2,oy2,1,-oh2,255);
    }
    if ( y1 > 0 && y2 > 0 ) {
      LineXY(ox1,oy1,ox2,oy2,255);
      LineXY(ox1,oy1-oh1,ox2,oy2-oh2,255);
    }
  }
}

void _DrawSprite2(double x, double y, double z, int tex, double rot) {
  double ox1, oy1, ox2, oy2, ox3, oy3, ox4, oy4, sScale, sStep, xPos, yPos;
  int ox, oy;
  if ( y > 0 ) {
    ox = ( ( x * ( height / 2 ) ) / y ) + ( width / 2 );
    oy = ( ( z * ( height / 2 ) ) / y ) + ( height / 2 );
    sScale = 1 / y;
    sStep = y;
    ox1 = ox - getTexX(tex)*sScale*(height/2);
    oy1 = oy - getTexY(tex)*sScale*(height/2);
    ox2 = ox1 + ( getTexWigth(tex)*sScale*(height/2) );
    oy2 = oy1;
    ox3 = ox1 + ( getTexWigth(tex)*sScale*(height/2) );
    oy3 = oy1 + ( getTexHeight(tex)*sScale*(height/2) );
    ox4 = ox1;
    oy4 = oy1 + ( getTexHeight(tex)*sScale*(height/2) );
    if ( DebugModeSprite != 0 ) {
      Box(ox1-2,oy1-2,5,5,255);
      Box(ox2-2,oy2-2,5,5,255);
      Box(ox3-2,oy3-2,5,5,255);
      Box(ox4-2,oy4-2,5,5,255);
      LineXY(ox1,oy1,ox2,oy2,255);
      LineXY(ox2,oy2,ox3,oy3,255);
      LineXY(ox3,oy3,ox4,oy4,255);
      LineXY(ox4,oy4,ox1,oy1,255);
    }
    if ( ox1 < 0 ) ox1 = 0;
    if ( ox1 > width-1 ) return;
    if ( ox2 < 0 ) return;
    if ( ox2 > width-1 ) ox2 = width-1;
    if ( ox3 < 0 ) return;
    if ( ox3 > width-1 ) ox3 = width-1;
    if ( ox4 < 0 ) ox4 = 0;
    if ( ox4 > width-1 ) return;
    if ( oy1 < 0 ) oy1 = 0;
    if ( oy1 > height-1 ) return;
    if ( oy2 < 0 ) oy2 = 0;
    if ( oy2 > height-1 ) return;
    if ( oy3 < 0 ) return;
    if ( oy3 > height-1 ) oy1 = height-1;
    if ( oy4 < 0 ) return;
    if ( oy4 > height-1 ) oy1 = height-1;
    if ( RenderSpriteTex != 0 ) {
      xPos = 0;
      for ( ox = ox1; ox <= ox2; ox++ ) {
        yPos = 0;
        for ( oy = oy1; oy <= oy4; oy++ ) {
          if ( zBuffer[ox][oy] > y ) {
            zBuffer[ox][oy] = y;
            plotPixel(ox,oy,getTexPixel(tex,xPos,yPos,rot));
          }
          yPos += sStep;
        }
        xPos += sStep;
      }
    } else {
      tex = getTexPixel(tex,xPos,yPos,rot);
      for ( ox = ox1; ox <= ox2; ox++ ) {
        for ( oy = oy1; oy <= oy4; oy++ ) {
          if ( zBuffer[ox][oy] > y ) {
            zBuffer[ox][oy] = y;
            plotPixel(ox,oy,tex);
          }
        }
      }
    }
  }
}

void _DrawFlat(double x1, double y1, double x2, double y2, double x3, double y3, double z, int tex, int cell) {
  if ( cell != 0 ) {
    if ( z < 0 ) {
      _DrawFlat2(x1,y1,x2,y2,x3,y3,z,tex,cell);
    }
  } else {
    if ( z > 0 ) {
      _DrawFlat2(x1,y1,x2,y2,x3,y3,z,tex,cell);
    }
  }
}

void _DrawWall(double x1, double y1, double x2, double y2, double z, double h, int tex) {
  _DrawWall2(x1,y1,x2,y2,z,h,tex);
}
void _DrawSprite(double x, double y, double z, int tex, int rot) {
  _DrawSprite2(x,y,z,tex,rot);
}
void DrawCelling(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double z, int tex) {
  _DrawFlat(x4,y4,x1,y1,x2,y2,z,tex,1);
  _DrawFlat(x2,y2,x3,y3,x4,y4,z,tex,1);
}
void DrawFlat(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double z, int tex) {
  _DrawFlat(x4,y4,x1,y1,x2,y2,z,tex,0);
  _DrawFlat(x2,y2,x3,y3,x4,y4,z,tex,0);
}
void DrawWall(double x1, double y1, double x2, double y2, double z, double h, int tex) {
  _DrawWall(x1,y1,x2,y2,z,h,tex);
}
void DrawSprite(double x, double y, double z, int tex, int rot) {
  _DrawSprite(x,y,z,tex,rot);
}

