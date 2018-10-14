#include <math.h>
#include <string.h>
#include "main.h"

typedef struct coordinate{
    int x1,y1,x2,y2;
}WindowType;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

int H_SIZE = 700;
int V_SIZE = 700;
int CANT_LINES = 2000;
int CANT_TIMES = 10000;
WindowType window;

int lineSet[2000][4];
int croppedLinesCS[2000][4];
int croppedLinesLB[2000][4];

void draw();
void drawLines();
void createLines();
void drawLines(int lines[][4]);
extern void line(int x0, int y0, int x1, int y1);

double cohenSutherland();
int getCode(int x, int y);

double liangBarsky();

int main(int argc, char** argv){

  window.x1 = 250;
  window.y1 = 250;
  window.x2 = H_SIZE - window.x1;
  window.y2 = H_SIZE - window.y1;

  createLines();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_STENCIL);
  glutInitWindowSize(H_SIZE,V_SIZE);
  glutCreateWindow("Tarea corta: Clipping");
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(-0.5, H_SIZE + 0.5, -0.5, V_SIZE + 0.5);
  glutDisplayFunc(draw);
  glutMainLoop();
}

void createLines(){
  srand(time(NULL));
  for (int i = 0; i < CANT_LINES; i++) {
    for (int j = 0; j < 4; j++) {
      lineSet[i][j] = rand() % H_SIZE;
    }
  }
}

void draw(){
  double timeCohenSutherland, timeLiangBarsky;

  setColor(1, 1, 1);
  drawLines(lineSet);

  setColor(1, 0, 0);
  timeCohenSutherland = cohenSutherland();
  drawLines(croppedLinesCS);

  setColor(0, 1, 0);
  timeLiangBarsky = liangBarsky();
  drawLines(croppedLinesCS);


  printf("\n");
  printf(" ================================================================ \n ");
  printf("| Cohen Sutherland \t\t |\t %.4f ms \t\t|\n", timeCohenSutherland);
  printf(" ---------------------------------------------------------------- \n ");
  printf("| Liang Barsky \t\t |\t %.4f ms \t\t|\n", timeLiangBarsky);
  printf(" ---------------------------------------------------------------- \n ");
  printf(" ================================================================ \n ");
}

void drawLines(int lines[][4]){
  for (int i = 0; i < CANT_LINES; i++) {
    line(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
    glFlush();
  }
}

double cohenSutherland(){
  clock_t startTime;
  double diffms;
  startTime = clock();

  int code1, code2, accept, x1, x2, y1, y2;

  for (int j = 0; j < CANT_TIMES; j++) {
    for (int i = 0; i < CANT_LINES; i++) {
      x1 = lineSet[i][0]; y1 = lineSet[i][1]; x2 = lineSet[i][2]; y2 = lineSet[i][3];

      code1 = getCode(x1, y1);
      code2 = getCode(x2, y2);
      accept = 0;

      while (1){
          if ((code1 == 0) && (code2 == 0)){
              accept = 1;
              break;
          }else if (code1 & code2){
              break;
          }else{
              int code_out = (code1 != 0) ? code1 : code2;
              int x, y;

              if (code_out & TOP){
                  x = x1 + (x2 - x1) * (window.y2 - y1) / (y2 - y1);
                  y = window.y2;
              }else if (code_out & BOTTOM){
                  x = x1 + (x2 - x1) * (window.y1 - y1) / (y2 - y1);
                  y = window.y1;
              }else if (code_out & RIGHT){
                  y = y1 + (y2 - y1) * (window.x2 - x1) / (x2 - x1);
                  x = window.x2;
              }else if (code_out & LEFT){
                  y = y1 + (y2 - y1) * (window.x1 - x1) / (x2 - x1);
                  x = window.x1;
              }

              if (code_out == code1){
                  x1 = x;
                  y1 = y;
                  code1 = getCode(x1, y1);
              }else{
                  x2 = x;
                  y2 = y;
                  code2 = getCode(x2, y2);
              }
          }
      }
      if (accept){
        croppedLinesCS[i][0] = x1;
        croppedLinesCS[i][1] = y1;
        croppedLinesCS[i][2] = x2;
        croppedLinesCS[i][3] = y2;
      }else{
        croppedLinesCS[i][0] = 0;
        croppedLinesCS[i][1] = 0;
        croppedLinesCS[i][2] = 0;
        croppedLinesCS[i][3] = 0;
      }
    }
  }

  diffms = (double) (clock() - startTime)/(CLOCKS_PER_SEC/1000);
  return diffms;
}


int getCode(int x, int y){
    int code = INSIDE;

    if (x < window.x1){
      code |= LEFT;
    }else if (x > window.x2){
      code |= RIGHT;
    }

    if (y < window.y1){
      code |= BOTTOM;
    }else if (y > window.y2){
      code |= TOP;
    }
    return code;
}


double liangBarsky(){
  clock_t startTime;
  double diffms;
  startTime = clock();

  int x1,y1,x2,y2,dx,dy;
  float t1,t2,p[4],q[4],temp;

  for (int k = 0; k < CANT_TIMES; k++) {
    for (int j = 0; j < CANT_LINES; j++) {
      x1 = lineSet[j][0]; y1 = lineSet[j][1]; x2 = lineSet[j][2]; y2 = lineSet[j][3];

      dx = x2-x1; dy = y2-y1;

      p[0] = -dx; p[1] = dx; p[2] = -dy; p[3] = dy;
      q[0] = x1-window.x1; q[1] = window.x2-x1; q[2] = y1-window.y1; q[3] = window.y2-y1;

      t1=0; t2=1;

      for(int i=0;i<4;i++){
        temp=q[i]/p[i];

        if(p[i]<0){
          if(t1<=temp){
            t1=temp;
          }
        } else{
          if(t2>temp){
            t2=temp;
          }
        }
      }

      if(t1 < t2){
        croppedLinesLB[j][0] = x1 + t1 * p[1];
        croppedLinesLB[j][1] = x1 + t2 * p[1];
        croppedLinesLB[j][2] = y1 + t1 * p[3];
        croppedLinesLB[j][3] = y1 + t2 * p[3];
      }
    }
  }


  diffms = (double) (clock() - startTime)/(CLOCKS_PER_SEC/1000);
  return diffms;
}
