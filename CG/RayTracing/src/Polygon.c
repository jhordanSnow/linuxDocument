#include "headers/main.h"

DistanceArray PolygonIntersection(Polygon* polygon, Ray* Rayo){
  DistanceArray objectTs = {0, NULL};
  double tDenominador = PointProduct(polygon->PolygonPlane->Normal, Rayo->Direction);
  if (tDenominador >= EPSILON){
    double t = - (PointProduct(polygon->PolygonPlane->Normal, Rayo->Anchor) + polygon->PolygonPlane->D) / tDenominador;
    Vector IntersectionPoint = CreateVector(
      Rayo->Anchor.X + t*Rayo->Direction.X,
      Rayo->Anchor.Y + t*Rayo->Direction.Y,
      Rayo->Anchor.Z + t*Rayo->Direction.Z
    );
  }

  return objectTs;
}

Vector PolygonNormal(Polygon* polygon){
  return polygon->PolygonPlane->Normal;
}
