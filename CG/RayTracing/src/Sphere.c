#include "headers/main.h"

DistanceArray SphereIntersection(Sphere* sphere, Vector Direction){
  DistanceArray objectTs;
  double a,b,c;

  a = 1.0;
  b = 2*(
          (Direction.X * (Eye.X - sphere->Center.X)) +
          (Direction.Y * (Eye.Y - sphere->Center.Y)) +
          (Direction.Z * (Eye.Z - sphere->Center.Z))
        );
  c = (Eye.X - sphere->Center.X)*(Eye.X - sphere->Center.X) +
      (Eye.Y - sphere->Center.Y)*(Eye.Y - sphere->Center.Y) +
      (Eye.Z - sphere->Center.Z)*(Eye.Z - sphere->Center.Z) -
      (sphere->Radius * sphere->Radius);

  objectTs = Solve2GradeEquation(a, b, c);

  return objectTs;
}

Vector SphereNormal(Sphere* sphere, Vector Point){
  Vector NormalDirection;

  NormalDirection = CreateVector(
      (Point.X - sphere->Center.X) / sphere->Radius,
      (Point.Y - sphere->Center.Y) / sphere->Radius,
      (Point.Z - sphere->Center.Z) / sphere->Radius
  );

  return NormalDirection;
}
