#include "headers/common.h"

Color CreateColor(int Alpha, int Red, int Green, int Blue){
  if (Alpha == EOF || Red == EOF || Green == EOF || Blue == EOF) {
     fprintf(stderr, "Unexpected end of file\n");
     exit(-1);
  }
  Color c =   {
                CreateVector(
                  (double) Red   / MAX_COLOR,
                  (double) Green / MAX_COLOR,
                  (double) Blue  / MAX_COLOR
                ),
                (double) Alpha / MAX_COLOR
              };
  return c;
}

Vector CreateVector(double X, double Y, double Z){
  Vector v = {X, Y, Z};
  return v;
}


void AllocateFrameBuffer(){
  FrameBuffer = calloc(H_SIZE, sizeof(Color *));
  for (int i = 0; i < H_SIZE; i++) {
    FrameBuffer[i] = calloc(V_SIZE, sizeof(Color));
  }
}

double CalculateNormal(Vector vector){
    double normal = sqrt(
      vector.X * vector.X +
      vector.Y * vector.Y +
      vector.Z * vector.Z
    );

    return normal;
}

Vector NormalizeVector(Vector vector){
  double Normal = CalculateNormal(vector);
  Vector v = CreateVector(
    vector.X / Normal,
    vector.Y / Normal,
    vector.Z / Normal
  );

  return v;
}

int LowerDistanceIndex(DistanceArray objectTs, double minT){
  int lowerIndex = -1;
  for (int i = 0; i < objectTs.size; i++) {
    if (objectTs.content[i] >= 0 && objectTs.content[i] <= minT){
      minT = objectTs.content[i];
      lowerIndex = i;
    }
  }
  return lowerIndex;
}

DistanceArray Solve2GradeEquation(double a, double b, double c){
  DistanceArray objectTs = {0, NULL};
  double disc;

  disc = (b*b) - (4*(a*c));

  if (disc == 0){
    printf("Discrimante es 0 whaaaaaaaaaaaaaaaaaaaaaat. \n");
    objectTs.size = 1;
    objectTs.content = calloc(objectTs.size, sizeof(double));
    objectTs.content[0] = -b/(2*a);
  }else if (disc > 0){
    objectTs.size = 2;
    objectTs.content = calloc(objectTs.size, sizeof(double));
    objectTs.content[0] = (-b - sqrt(disc))/(2*a);
    objectTs.content[1] = (-b + sqrt(disc))/(2*a);
  }

  return objectTs;
}


double PointProduct(Vector Vector1, Vector Vector2){
  double cosAngle;
  cosAngle = (Vector1.X * Vector2.X) + (Vector1.Y * Vector2.Y) + (Vector1.Z * Vector2.Z);
  return cosAngle;
}
