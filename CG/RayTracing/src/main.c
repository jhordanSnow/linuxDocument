#include "headers/main.h"

void main(int argc, char** argv){
  //FileToFrameBuffer("input/test.avs");
  InitializeDesignerVariables();
  AllocateFrameBuffer();
  LoadScene(argv[1]);
  RayTracer();

  FrameBufferToFile("output/result.avs");
}

void InitializeDesignerVariables(){
  H_SIZE = 1008;
  V_SIZE = 567;

  CantPlanes = 0;
  Planes = calloc(CantPlanes, sizeof(Plane*));

  // Luces
  AmbientLight = 0.2;
  CantLights = 3;
  Lights = calloc(CantLights, sizeof(Light));

  Lights[0].Position = CreateVector(-200.0, -120.0, 300.0);
  Lights[0].Kn = 100;
  Lights[0].Intensity = 1.0;
  Lights[0].AttenuationC1 = 0.05;
  Lights[0].AttenuationC2 = 0.005;
  Lights[0].AttenuationC3 = 0.0;


  Lights[1].Position = CreateVector(0.0, 20.0, 300.0);
  Lights[1].Kn = 3;
  Lights[1].Intensity = 0.7;
  Lights[1].AttenuationC1 = 0.05;
  Lights[1].AttenuationC2 = 0.005;
  Lights[1].AttenuationC3 = 0.0;

  Lights[2].Position = CreateVector(200.0, -60.0, 550.0);
  Lights[2].Kn = 2;
  Lights[2].Intensity = 0.2;
  Lights[2].AttenuationC1 = 0.05;
  Lights[2].AttenuationC2 = 0.005;
  Lights[2].AttenuationC3 = 0.0;

  BACKGROUND = CreateColor(255.0, 80.75, 80.75, 80.75);

  Eye = CreateVector(50.0, 15.0, -400.0);

  Window.Min = CreateVector(-50.4, -28.3, 0.0);
  Window.Max = CreateVector( 50.4,  28.4, 0.0);
}


void RayTracer(){
  int i, j;
  Color PixelColor;
  Vector Pixel;

  Ray Rayo = {Eye, Eye};

  for (i = 0; i < H_SIZE; i++) {
    for (j = 0; j < V_SIZE; j++) {

      Pixel = CreateVector(
        (i + 0.5) * ((Window.Max.X - Window.Min.X) / H_SIZE) + Window.Min.X,
        (j + 0.5) * ((Window.Max.Y - Window.Min.Y) / V_SIZE) + Window.Min.Y,
        0
      );

      Rayo.Direction = NormalizeVector(CreateVector(Pixel.X - Eye.X,Pixel.Y - Eye.Y,Pixel.Z - Eye.Z));

      PixelColor = GetColor(&Rayo);

      FrameBuffer[i][j] = PixelColor;
    }
  }
}


Color GetColor(Ray* Rayo){
  Color color;
  Intersection* intersection = GetFirstIntersection(Rayo);

  if (!intersection->ObjectContainer){
    color =  BACKGROUND;
  }else{
    color = intersection->ObjectContainer->color;
    IntensityReturn* Intensity = GetLightIntensity(Rayo, intersection);
    color.RGB = ScalarVector(color.RGB, Intensity->LightIntensity);

    color.RGB = CreateVector(
      color.RGB.X + (Intensity->EspecularReflexion * (1.0 - color.RGB.X)),
      color.RGB.Y + (Intensity->EspecularReflexion * (1.0 - color.RGB.Y)),
      color.RGB.Z + (Intensity->EspecularReflexion * (1.0 - color.RGB.Z))
    );
  }

  return color;
}

Intersection* GetFirstIntersection(Ray* Rayo){
  int lowerIndex, i;
  Intersection* inter = calloc(1, sizeof(Intersection));
  Node* current = First;
  double minT = DBL_MAX;

  for (i = 0; i < CantObjects; i++) {
    DistanceArray objectTs = GetIntersections(Rayo, current->type, current->object);
    if (objectTs.size > 0){
      lowerIndex = LowerDistanceIndex(objectTs, minT);

      if (lowerIndex >= 0){
        minT = objectTs.content[lowerIndex];
        inter->lowerIndex = lowerIndex;
        inter->t = objectTs;
        inter->ObjectContainer = current;
      }
    }
    current = current->next;
  }
  return inter;
}

DistanceArray GetIntersections(Ray* Rayo, ObjectType type ,void* object){
  DistanceArray objectTs = {0, NULL};
  Ray* RayTmp = calloc(1, sizeof(Ray));
  RayTmp = Rayo;

  if (type == SPHERE){
    objectTs = ((Sphere*) object)->GetIntersection(((Sphere*) object), RayTmp);
  }else if(type == POLYGON){
    objectTs = ((Polygon*) object)->GetIntersection(((Polygon*) object), RayTmp);
  }

  return objectTs;
}

IntensityReturn* GetLightIntensity(Ray* Rayo, Intersection* intersection){
  double LIntensity, LEspecular, t, LDistance, Fatt, NLProduct, LI;
  float KD, KA, KS, PointProductExpo;
  Vector L, N, V, R, Point, DistanceVector;
  t = intersection->t.content[intersection->lowerIndex];

  Point = CreateVector(
    Rayo->Anchor.X + (t * Rayo->Direction.X),
    Rayo->Anchor.Y + (t * Rayo->Direction.Y),
    Rayo->Anchor.Z + (t * Rayo->Direction.Z)
  );

  KD = intersection->ObjectContainer->DiffusionCoefficient;
  KA = intersection->ObjectContainer->AmbientCoefficient;
  KS = intersection->ObjectContainer->EspecularCoefficient;

  if (intersection->ObjectContainer->type == SPHERE){
    N = ((Sphere*) intersection->ObjectContainer->object)->GetNormal(((Sphere*) intersection->ObjectContainer->object), Point);
  }

  V = ScalarVector(Rayo->Direction, -1.0);

  for (int i = 0; i < CantLights; i++) {
    DistanceVector = CreateVector(
      Lights[i].Position.X - Point.X,
      Lights[i].Position.Y - Point.Y,
      Lights[i].Position.Z - Point.Z
    );
    LDistance = CalculateNormal(DistanceVector);

    L = CreateVector(
        (DistanceVector.X) / LDistance,
        (DistanceVector.Y) / LDistance,
        (DistanceVector.Z) / LDistance
    );

    NLProduct = PointProduct(N, L);
    R = SubVector(ScalarVector(N, NLProduct * 2), L);

    Ray* RayoLight = calloc(1, sizeof(Ray));
    RayoLight->Anchor = Point;
    RayoLight->Direction = L;

    Intersection* intersectionLight = GetFirstIntersection(RayoLight);
    if (!intersectionLight->ObjectContainer){
      Fatt = 1 / (
        Lights[i].AttenuationC1 +
        (Lights[i].AttenuationC2 * LDistance) +
        (Lights[i].AttenuationC3 * LDistance * LDistance)
      );

      LI = Lights[i].Intensity;
      Fatt = (Fatt > 1.0) ? 1.0 : Fatt;

      float ProductTmp = PointProduct(R, V);
      PointProductExpo = ProductTmp;

      for (int j = 1; j < Lights[i].Kn; j++) {
        PointProductExpo *= ProductTmp;
      }

      LEspecular += (
                      PointProductExpo * KS *
                      LI * Fatt
                    );

      LIntensity += (
                          PointProduct(L, N) * KD *
                          LI * Fatt
                        ) +
                        (AmbientLight * KA);
    }
  }

  LIntensity = (LIntensity > 1) ? 1 : LIntensity;
  LIntensity = (LIntensity < 0) ? 0 : LIntensity;

  LEspecular = (LEspecular > 1) ? 1 : LEspecular;
  LEspecular = (LEspecular < 0) ? 0 : LEspecular;

  IntensityReturn* Intensity = calloc(1, sizeof(IntensityReturn));
  Intensity->LightIntensity = LIntensity;
  Intensity->EspecularReflexion = LEspecular;

  return Intensity;
}

void LoadScene(char* Filename){
  if (!Filename){
    printf("Escena no especificada.\n");
    exit(0);
  }

  FILE *file = fopen(Filename, "r");

  if (file == NULL){
    printf("No existe el archivo de la escena.\n");
    exit(0);
  }

  CantObjects = 0;
  Node* CurrentObject;
  char fileContent[20];
  double a, r, g, b, radius, x, y, z;

  do {
    Node* Object = calloc(1, sizeof(Node));

    fscanf(file, "%s", fileContent);
    Object->type = atoi(fileContent);

    if (Object->type == SPHERE){
      InitSphere(file, Object);
    }
    else if(Object->type == POLYGON){
      InitPolygon(file, Object);
    }

    if (CantObjects == 0){
      First = Object;
    }else{
      CurrentObject->next = Object;
    }

    CurrentObject = Object;
    CantObjects++;

    fscanf(file, "%s", fileContent);
  } while(strcmp(fileContent, ";") != 0);

  printf("Cantidad de objetos: %d\n", CantObjects);

  fclose(file);
}


void InitObjects(FILE* file, Node* Object){
  double a,r,g,b;
  char fileContent[420];

  fscanf(file, "%s", fileContent);
  Object->DiffusionCoefficient = atof(fileContent);

  fscanf(file, "%s", fileContent);
  Object->EspecularCoefficient = atof(fileContent);

  fscanf(file, "%s", fileContent);
  Object->AmbientCoefficient = atof(fileContent);

  fscanf(file, "%s", fileContent);
  a = atof(fileContent);
  fscanf(file, "%s", fileContent);
  r = atof(fileContent);
  fscanf(file, "%s", fileContent);
  g = atof(fileContent);
  fscanf(file, "%s", fileContent);
  b = atof(fileContent);

  Object->color = CreateColor(a, r, g, b);
}


void InitSphere(FILE* file, Node* Object){
  InitObjects(file, Object);

  double x,y,z;
  char fileContent[420];

  Object->object = calloc(1, sizeof(Sphere));

  fscanf(file, "%s", fileContent);
  ((Sphere*) Object->object)->Radius = atof(fileContent);

  fscanf(file, "%s", fileContent);
  x = atof(fileContent);
  fscanf(file, "%s", fileContent);
  y = atof(fileContent);
  fscanf(file, "%s", fileContent);
  z = atof(fileContent);

  ((Sphere*) Object->object)->Center = CreateVector(x, y, z);
  ((Sphere*) Object->object)->GetIntersection = &SphereIntersection;
  ((Sphere*) Object->object)->GetNormal = &SphereNormal;
}

void InitPlane(FILE* file){
  double x,y,z;
  char fileContent[420];

  CantPlanes++;
  Planes = realloc(*Planes, CantPlanes * sizeof(Plane*));
  Plane* ReadPlane = calloc(1, sizeof(Plane));

  fscanf(file, "%s", fileContent);
  x = atof(fileContent);
  fscanf(file, "%s", fileContent);
  y = atof(fileContent);
  fscanf(file, "%s", fileContent);
  z = atof(fileContent);
  Vector Anchor = CreateVector(x, y, z);

  fscanf(file, "%s", fileContent);
  x = atof(fileContent);
  fscanf(file, "%s", fileContent);
  y = atof(fileContent);
  fscanf(file, "%s", fileContent);
  z = atof(fileContent);
  ReadPlane->Normal = CreateVector(x, y, z);
  ReadPlane->D = -PointProduct(ReadPlane->Normal, Anchor);

  Planes[CantPlanes-1] = ReadPlane;
}

void InitPolygon(FILE* file, Node* Object){
  InitObjects(file, Object);
  int vertexCount;
  char fileContent[420];
  Object->object = calloc(1, sizeof(Polygon));
  fscanf(file, "%s", fileContent);
  vertexCount = atoi(fileContent);
  double x,y,z;
  ((Polygon*) Object->object)->VertexCount = vertexCount;
  ((Polygon*) Object->object)->Vertices = calloc(vertexCount, sizeof(Vector*));

  for(int i = 0; i < vertexCount ; i++){
    fscanf(file, "%s", fileContent);
    x = atof(fileContent);
    fscanf(file, "%s", fileContent);
    y = atof(fileContent);
    fscanf(file, "%s", fileContent);
    z = atof(fileContent);
    ((Polygon*) Object->object)->Vertices[i] = CreateVector(x,y,z);
  }
  Vector v1 = ((Polygon*) Object->object)->Vertices[0];
  Vector v2 = ((Polygon*) Object->object)->Vertices[1];
  Vector v3 = ((Polygon*) Object->object)->Vertices[2];
  ((Polygon*) Object->object)->PolygonPlane = PlaneFromPoints(v1, v2,v3);

  ((Polygon*) Object->object)->GetIntersection = &PolygonIntersection;
  ((Polygon*) Object->object)->GetNormal = &PolygonNormal;
}

Plane* PlaneFromPoints(Vector v1, Vector v2, Vector v3 ){
  Vector vTmp1 = SubVector(v2, v1);
  Vector vTmp2 = SubVector(v3, v1);
  Vector PlaneNormal = CrossProduct(vTmp1, vTmp2);
  CantPlanes++;

  Plane* PolygonPlane = calloc(1, sizeof(Plane));
  PolygonPlane->Normal = PlaneNormal;
  PolygonPlane->D = -PointProduct(PlaneNormal, v1);

  return PolygonPlane;
}
