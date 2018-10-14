#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "malloc.h"
#include "time.h"
#include "sys/time.h"
#include "unistd.h"
#include "common.h"

#include <math.h>

typedef struct {
  float x;
  float y;
} vector;
vector createVector(int x, int y);

vector createVector(int x, int y);
vector addVector(vector a, vector b);
vector scalarMult(vector a, float s);
vector bezierEquation4(float t, vector p1, vector p2, vector p3, vector p4);
void printVector(vector a);
vector roundVector(vector a);

void draw_scene ();

extern void line(int x0, int y0, int x1, int y1);

void draw();
void mark();
void noplot(int x, int y);
void drawBezier(vector p1, vector p2, vector p3, vector p4, int segments);

int H_SIZE = 1272;
int V_SIZE = 450;

int main(int argc, char** argv) {

  srand(time(NULL));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_STENCIL);
  glutInitWindowSize(H_SIZE,V_SIZE);
  glutCreateWindow("Tarea corta: Bezier");
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(-0.5, H_SIZE + 0.5, -0.5, V_SIZE + 0.5);

  glutDisplayFunc(draw);
  glutMainLoop();
}

void signature () {
  setColor(0, 0, 0);
  int delay = 200000;


  drawBezier( createVector( 110 , 302 ), createVector( 312 , 326 ), createVector( 472 , 539 ), createVector( 417 , 457 ), 100);
  drawBezier( createVector( 417 , 457 ), createVector( 375 , 396 ), createVector( 331 , 250 ), createVector( 278 , 174 ), 100);
  drawBezier( createVector( 278 , 174 ), createVector( 213 , 80 ), createVector( 90 , -1 ), createVector( 36 , 10 ), 100);
  drawBezier( createVector( 306 , 148 ), createVector( 405 , 191 ), createVector( 417 , 210 ), createVector( 518 , 268 ), 100);
  drawBezier( createVector( 518 , 268 ), createVector( 588 , 308 ), createVector( 349 , 165 ), createVector( 417 , 121 ), 100);
  drawBezier( createVector( 417 , 121 ), createVector( 481 , 80 ), createVector( 645 , 251 ), createVector( 600 , 191 ), 100);
  drawBezier( createVector( 600 , 191 ), createVector( 582 , 167 ), createVector( 526 , 118 ), createVector( 578 , 118 ), 100);
  drawBezier( createVector( 578 , 118 ), createVector( 617 , 118 ), createVector( 656 , 162 ), createVector( 709 , 157 ), 100);
  drawBezier( createVector( 709 , 157 ), createVector( 732 , 155 ), createVector( 742 , 150 ), createVector( 761 , 129 ), 100);

  // <bpy_struct, Curve("BezierCurve.002")>
  drawBezier( createVector( 1000 , 420 ), createVector( 1035 , 482 ), createVector( 941 , 448 ), createVector( 927 , 444 ), 100);
  drawBezier( createVector( 927 , 444 ), createVector( 887 , 433 ), createVector( 839 , 403 ), createVector( 817 , 378 ), 100);
  drawBezier( createVector( 817 , 378 ), createVector( 778 , 333 ), createVector( 733 , 267 ), createVector( 761 , 224 ), 100);
  drawBezier( createVector( 761 , 224 ), createVector( 774 , 203 ), createVector( 796 , 190 ), createVector( 819 , 199 ), 100);
  drawBezier( createVector( 819 , 199 ), createVector( 935 , 247 ), createVector( 1016 , 315 ), createVector( 966 , 271 ), 100);
  drawBezier( createVector( 966 , 271 ), createVector( 848 , 167 ), createVector( 757 , 58 ), createVector( 674 , 9 ), 100);
  drawBezier( createVector( 893 , 134 ), createVector( 930 , 129 ), createVector( 967 , 150 ), createVector( 1012 , 168 ), 100);
  drawBezier( createVector( 1012 , 168 ), createVector( 1067 , 191 ), createVector( 1052 , 194 ), createVector( 1158 , 238 ), 100);
  drawBezier( createVector( 1158 , 238 ), createVector( 1203 , 257 ), createVector( 1064 , 179 ), createVector( 1063 , 140 ), 100);
  drawBezier( createVector( 1063 , 140 ), createVector( 1063 , 125 ), createVector( 1076 , 126 ), createVector( 1090 , 125 ), 100);
  drawBezier( createVector( 1090 , 125 ), createVector( 1114 , 124 ), createVector( 1134 , 136 ), createVector( 1201 , 158 ), 100);
  drawBezier( createVector( 1201 , 158 ), createVector( 1225 , 165 ), createVector( 1233 , 171 ), createVector( 1249 , 161 ), 100);
  drawBezier( createVector( 1249 , 161 ), createVector( 1260 , 154 ), createVector( 1252 , 139 ), createVector( 1261 , 129 ), 100);
  drawBezier( createVector( 1261 , 129 ), createVector( 1273 , 118 ), createVector( 1285 , 116 ), createVector( 1302 , 116 ), 100);
  drawBezier( createVector( 1302 , 116 ), createVector( 1312 , 116 ), createVector( 1348 , 130 ), createVector( 1379 , 135 ), 100);
  drawBezier( createVector( 1379 , 135 ), createVector( 1406 , 139 ), createVector( 1412 , 149 ), createVector( 1448 , 139 ), 100);
}

void draw() {
  signature();
  glFlush();
}

void noplot(int x, int y) {
  return;
}

void drawBezier(vector p1, vector p2, vector p3, vector p4, int segments) {
  int i;

  vector oldV = roundVector(p1);
  for (i = 1; i <= segments; i++) {
    vector newV = roundVector(bezierEquation4(i / (float)segments, p1, p2, p3, p4));
    line(oldV.x, oldV.y, newV.x, newV.y);
    oldV = newV;
  }
}

vector bezierEquation4(float t, vector p1, vector p2, vector p3, vector p4) {
  vector term1 = scalarMult(p1, pow(1-t, 3));
  vector term2 = scalarMult(p2, pow(1-t, 2)*t*3) ;
  vector term3 = scalarMult(p3, (1-t)*pow(t,2)*3) ;
  vector term4 = scalarMult(p4, pow(t, 3));

  vector add12 = addVector(term1, term2);
  vector add34 = addVector(term3, term4);
  return addVector(add12, add34);
}

vector createVector(int x, int y) {
  return (vector){x*0.8, y*0.8};
}

vector addVector(vector a, vector b) {
  return (vector){a.x + b.x, a.y + b.y};
}

vector scalarMult(vector a, float s) {
  return (vector){a.x * s, a.y * s};
}

void printVector(vector a) {
  printf("(%f, %f)", a.x, a.y);
}

vector roundVector(vector a) {
  return (vector){round(a.x), round(a.y)};
}
