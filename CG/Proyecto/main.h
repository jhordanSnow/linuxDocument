#ifndef LINES_H
#define LINES_H
#include <math.h>

#define H_SIZE 600
#define V_SIZE 600

extern void line(int x0, int y0, int x1, int y1);
typedef struct {
  float x;
  float y;
} vector;
vector createVector(int x, int y);

typedef struct {
  vector botLeft;
  vector topRight;
  vector resolution;
} Window;

vector createVector(int x, int y);
vector addVector(vector a, vector b);
vector subVector(vector a, vector b);
vector scalarMult(vector a, float s);
vector bezierEquation4(float t, vector p1, vector p2, vector p3, vector p4);
void printVector(vector a);
vector roundVector(vector a);
#endif
