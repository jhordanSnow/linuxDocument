#include <math.h>
#include <stdlib.h>

void line1(int x0, int y0, int x1, int y1, void (*plotToUse)(int,int)){
  long double m, b, y, x;
  int i, tmp;

  m = (long double)(y1 - y0) / (x1 - x0);
  b = (long double)y0 - m*x0;

  if (m >= 1 || m <= -1){
    if (y0 > y1){
      tmp = x0;x0 = x1;x1 = tmp;
      tmp = y0;y0 = y1;y1 = tmp;
    }

    if (x0 == x1){
      for (i = y0; i <= y1; i++) {
        plotToUse(x0, i);
      }
    }else{
      for (i = y0; i <= y1; i++) {
        x = ((long double)i - b)/m;
        plotToUse(round(x), i);
      }
    }

  }else{
    if (x0 > x1){
      tmp = x0;x0 = x1;x1 = tmp;
      tmp = y0;y0 = y1;y1 = tmp;
    }

    for (i = x0; i <= x1; i++) {
      y = m*i + b;
      plotToUse(i, round(y));
    }
  }
}


void line2(int x0, int y0, int x1, int y1, void (*plotToUse)(int,int)){
  long double m, y, x;
  int i, tmp;

  m = (long double)(y1 - y0) / (x1 - x0);
  y = (long double)y0;
  x = (long double)x0;

  if (m >= 1 || m <= -1){
    if (y0 > y1){
      tmp = x0;x0 = x1;x1 = tmp;
      tmp = y0;y0 = y1;y1 = tmp;
      x = (long double)x0;
    }
    m = 1/m;

    for (i = y0; i <= y1; i++) {
      plotToUse(round(x), i);
      x += m;
    }
  }else{
    if (x0 > x1){
      tmp = x0;x0 = x1;x1 = tmp;
      tmp = y0;y0 = y1;y1 = tmp;
      y = (long double)y0;
    }

    for (i = x0; i <= x1; i++) {
      plotToUse(i, round(y));
      y += m;
    }
  }
}


void line3(int x0, int y0, int x1, int y1, void (*plotToUse)(int,int)){
  long double y, x, paso_x, paso_y;
  int i, ancho;

  ancho = fmax(abs(x1 - x0), abs(y1 - y0));
  paso_x = (long double)(x1 - x0)/ancho;
  paso_y = (long double)(y1 - y0)/ancho;
  x = x0; y = y0;
  for (int i = 0; i <= ancho; i++) {
    plotToUse(round(x), round(y));
    x += paso_x;
    y += paso_y;
  }
}

/*
 * Algoritmo de Bresenham
 */

void line4(int x0, int y0, int x1, int y1, void (*plotToUse)(int,int)){
  int diffX, diffY, movX, movY, err, errTmp;

  if (x0 < x1){
    diffX = x1-x0;
    movX = 1;
  }else{
    diffX = x0-x1;
    movX = -1;
  }

  if (y0 < y1){
    diffY = y1-y0;
    movY = 1;
  }else{
    diffY = y0-y1;
    movY = -1;
  }
/*
  diffX = (x1-x0) >= 0 ? x1-x0 : -1*(x1-x0);
  diffY = (y1-y0) >= 0 ? y1-y0 : -1*(y1-y0);

  movX = x0 < x1 ? 1 : -1;
  movY = y0 < y1 ? 1 : -1;
*/
  err = (diffX >= diffY ? diffX : -diffY);

  diffX *= 2; diffY *= 2;

  while(!(x0 == x1 && y0 == y1)){

    plotToUse(x0,y0);
    errTmp = err;
    if (errTmp < diffY) {
      err += diffX; y0 += movY;
    }
    if (-errTmp < diffX) {
      err -= diffY; x0 += movX;
    }
  }
  plotToUse(x0,y0);
}
