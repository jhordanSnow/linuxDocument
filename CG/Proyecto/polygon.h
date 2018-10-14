
/*
 * Instituto Tecnologico de Costa Rica
 * Escuela de Ingenieria en Computacion
 * Computer Graphics
 *
 * Programa: line
 * Archivo:  line.h
 */
#ifndef POLYGON_H
#define POLYGON_H
#include "main.h"
#include "clipper.h"
#include "filler.h"

typedef struct {
  int length;
  vector* points;
} Polygon;

void showPolygonLines(Polygon polygon, Window w);
void showPolygonLinesWindow(Polygon polygon);
Polygon worldPoligonToWindow (Polygon p, Window w);
Polygon clipPolygon(Polygon polygon, Window w);

void fillPolygon(Polygon p);
#endif
