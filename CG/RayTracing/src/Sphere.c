#include "headers/main.h"

DistanceArray SphereIntersection(Sphere* sphere, Ray* Rayo){
  DistanceArray objectTs;
  double a,b,c;

  a = 1.0;
  b = 2*(
          (Rayo->Direction.X * (Rayo->Anchor.X - sphere->Center.X)) +
          (Rayo->Direction.Y * (Rayo->Anchor.Y - sphere->Center.Y)) +
          (Rayo->Direction.Z * (Rayo->Anchor.Z - sphere->Center.Z))
        );
  c = (Rayo->Anchor.X - sphere->Center.X)*(Rayo->Anchor.X - sphere->Center.X) +
      (Rayo->Anchor.Y - sphere->Center.Y)*(Rayo->Anchor.Y - sphere->Center.Y) +
      (Rayo->Anchor.Z - sphere->Center.Z)*(Rayo->Anchor.Z - sphere->Center.Z) -
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
