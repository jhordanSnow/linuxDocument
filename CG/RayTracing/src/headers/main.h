#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define MAX_COLOR 255
#define EPSILON 0.00005

typedef enum { SPHERE } ObjectType;

typedef struct Vector{
  double X,Y,Z;
}Vector;

typedef struct Ray{
    Vector Anchor;
    Vector Direction;
}Ray;

typedef struct Color{
  Vector RGB;
  double A;
}Color;

typedef struct Cube{
 Vector Min;
 Vector Max;
}Cube;

typedef struct DistanceArray{
  int size;
  double* content;
}DistanceArray;

typedef struct Sphere{
  Vector Center;
  double Radius;
  DistanceArray (*GetIntersection)(struct Sphere*, struct Vector);
  Vector (*GetNormal)(struct Sphere*, struct Vector);
}Sphere;

typedef struct Node{
  struct Node* next;
  struct Node* prevous;
  void* object;
  Color color;
  ObjectType type;
  double DiffusionCoefficient;
  double AmbientCoefficient;
}Node;

typedef struct Intersection{
  Node* ObjectContainer;
  int lowerIndex;
  DistanceArray t;
}Intersection;

typedef struct Light{
  Vector Position;
  double Intensity;
  double AttenuationC1;
  double AttenuationC2;
  double AttenuationC3;
}Light;

/* ------- Diseñador ----------  */

unsigned int H_SIZE;
unsigned int V_SIZE;
Color BACKGROUND;
Vector Eye;
Cube Window;
int CantObjects;
Node* First;
int CantLights;
Light* Lights;
Color** FrameBuffer;
double AmbientLight;

/* Common functions */
Vector CreateVector(double X, double Y, double Z);
Color CreateColor(int Alpha, int Red, int Green, int Blue);
DistanceArray Solve2GradeEquation(double a, double b, double c);
double CalculateNormal(Vector vector);
Vector NormalizeVector(Vector vector);
void AllocateFrameBuffer();
int LowerDistanceIndex(DistanceArray objectTs, double minT);
double PointProduct(Vector L, Vector N);
void LoadScene(char* Filename);

/* File functions */
void FileToFrameBuffer(char* file);
void FrameBufferToFile(char* file);

/* Main Functions */
void InitializeDesignerVariables();
void RayTracer();
Color GetColor(Vector Direction);
Intersection* GetFirstIntersection(Vector Direction);
DistanceArray GetIntersections(Vector Direction, ObjectType type ,void* object);
double GetLightIntensity(Vector Direction, Intersection* intersection);

/* Objects Functions */
DistanceArray SphereIntersection(Sphere* sphere, Vector Direction);
Vector SphereNormal(Sphere* sphere, Vector Point);
