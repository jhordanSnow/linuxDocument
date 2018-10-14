#include "common.h"

int validateEntry(char entry[]){
  int i = 0;
  if (entry[0] == '-') return 0;
  for (; entry[i] != 0; i++){
    if (entry[i] > '9' || entry[i] < '0') return 0;
  }
  return 1;
}

void setColor(double r, double g, double b){
  CURRENT_COLOR.r = r;
  CURRENT_COLOR.g = g;
  CURRENT_COLOR.b = b;
}

void plot(int x, int y){
  glBegin(GL_POINTS);
  glColor3f(CURRENT_COLOR.r, CURRENT_COLOR.g, CURRENT_COLOR.b);
  glVertex2i(x, y);
  glEnd();
  //glFlush();
}

void plotClean(int x, int y){}


vector createVector(int x, int y) {
  return (vector){x, y};
}

vector addVector(vector a, vector b) {
  return (vector){a.x + b.x, a.y + b.y};
}

vector subVector(vector a, vector b) {
  return (vector){a.x - b.x, a.y - b.y};
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
