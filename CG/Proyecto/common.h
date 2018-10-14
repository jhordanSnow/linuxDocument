#ifndef COMMON_H
#define COMMON_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <time.h>
#include <stdio.h>
#include "main.h"

typedef struct {double r;double g;double b;} COLOR;
COLOR CURRENT_COLOR;

int validateEntry(char entry[]);
void setColor(double r, double g, double b);
void plot(int x, int y);
void plotClean(int x, int y);

#endif
