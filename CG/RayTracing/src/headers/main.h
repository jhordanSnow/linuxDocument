#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define MAX_COLOR 255
#define EPSILON 0.00005

typedef enum { SPHERE, POLYGON, PLANE } ObjectType;

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
  DistanceArray (*GetIntersection)(struct Sphere*, struct Ray*);
  Vector (*GetNormal)(struct Sphere*, struct Vector);
}Sphere;

typedef struct Plane{
  double D;
  Vector Normal;
}Plane;

typedef struct Polygon{
  int VertexCount;
  Vector* Vertices;
  Plane* PolygonPlane;
  DistanceArray (*GetIntersection)(struct Polygon*, struct Ray*);
  Vector (*GetNormal)(struct Polygon*);
}Polygon;

typedef struct Node{
  struct Node* next;
  struct Node* prevous;
  void* object;
  Color color;
  ObjectType type;
  double DiffusionCoefficient;
  double EspecularCoefficient;
  double AmbientCoefficient;
}Node;

typedef struct Intersection{
  Node* ObjectContainer;
  int lowerIndex;
  DistanceArray t;
}Intersection;

typedef struct Light{
  Vector Position;
  int Kn;
  double Intensity;
  double AttenuationC1;
  double AttenuationC2;
  double AttenuationC3;
}Light;

typedef struct IntensityReturn{
  double LightIntensity;
  double EspecularReflexion;
}IntensityReturn;

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

int CantPlanes;
Plane** Planes;


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
Vector CrossProduct(Vector v1, Vector v2);
Vector ScalarVector(Vector v, double e);
Vector SubVector(Vector v1, Vector v2);
Vector SumVector(Vector v1, Vector v2);

/* File functions */
void FileToFrameBuffer(char* file);
void FrameBufferToFile(char* file);

/* Main Functions */
void InitializeDesignerVariables();
void RayTracer();
Color GetColor(Ray* Rayo);
Intersection* GetFirstIntersection(Ray* Rayo);
DistanceArray GetIntersections(Ray* Rayo, ObjectType type ,void* object);
IntensityReturn* GetLightIntensity(Ray* Rayo, Intersection* intersection);

void InitObjects(FILE* file, Node* Object);
void InitSphere(FILE* file, Node* Object);
void InitPlane(FILE* file);
void InitPolygon(FILE* file, Node* Object);
Plane* PlaneFromPoints(Vector v1, Vector v2, Vector v3);

/* Objects Functions */
DistanceArray SphereIntersection(Sphere* sphere, Ray* Rayo);
Vector SphereNormal(Sphere* sphere, Vector Point);

DistanceArray PolygonIntersection(Polygon* polygon, Ray* Rayo);
Vector PolygonNormal(Polygon* polygon);
