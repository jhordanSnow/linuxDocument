#include "polygon.h"
#include <stdlib.h>
#include <stdio.h>

vector worldVectorToWindow (vector v, Window w) {
  vector newVector = (vector) {
    ((float)((float)v.x - w.botLeft.x)/(float)((float)w.topRight.x - w.botLeft.x) * (float)w.resolution.x),
    ((float)((float)v.y - w.botLeft.y)/(float)((float)w.topRight.y - w.botLeft.y) * (float)w.resolution.y)
  };
  return newVector;
}

Polygon worldPoligonToWindow(Polygon polygon, Window w){
  vector *v = (vector*)malloc(sizeof(vector) * polygon.length);
  int i;

  for (i = 0; i < polygon.length; i++){
    v[i] = worldVectorToWindow(polygon.points[i], w);
  }

  return (Polygon) {
    polygon.length,
    v
  };
}

void showPolygonLines(Polygon polygon, Window w) {
  int i;
  vector prev = worldVectorToWindow (polygon.points[0], w);
  vector last = worldVectorToWindow (polygon.points[polygon.length - 1], w);
  line(prev.x, prev.y, last.x, last.y);
  for (i = 1; i < polygon.length; i++) {
    vector curr = worldVectorToWindow (polygon.points[i], w);
    line(prev.x, prev.y, curr.x, curr.y);
    prev = curr;
  }
}

void showPolygonLinesWindow(Polygon polygon) {
  int i;
  vector prev = polygon.points[0];
  vector last = polygon.points[polygon.length - 1];
  line(prev.x, prev.y, last.x, last.y);
  for (i = 1; i < polygon.length; i++) {
    vector curr = polygon.points[i];
    line(prev.x, prev.y, curr.x, curr.y);
    prev = curr;
  }
}
