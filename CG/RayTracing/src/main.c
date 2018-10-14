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

  // Luces
  AmbientLight = 0.2;
  CantLights = 3;
  Lights = calloc(CantLights, sizeof(Light));

  Lights[0].Position = CreateVector(-200.0, -120.0, 300.0);
  Lights[0].Intensity = 1.0;
  Lights[0].AttenuationC1 = 0.05;
  Lights[0].AttenuationC2 = 0.005;
  Lights[0].AttenuationC3 = 0.0;


  Lights[1].Position = CreateVector(0.0, 20.0, 300.0);
  Lights[1].Intensity = 0.7;
  Lights[1].AttenuationC1 = 0.05;
  Lights[1].AttenuationC2 = 0.005;
  Lights[1].AttenuationC3 = 0.0;

  Lights[2].Position = CreateVector(200.0, -60.0, 550.0);
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
  Vector Pixel, Direction;

  for (i = 0; i < H_SIZE; i++) {
    for (j = 0; j < V_SIZE; j++) {

      Pixel = CreateVector(
        (i + 0.5) * ((Window.Max.X - Window.Min.X) / H_SIZE) + Window.Min.X,
        (j + 0.5) * ((Window.Max.Y - Window.Min.Y) / V_SIZE) + Window.Min.Y,
        0
      );

      Direction = NormalizeVector(CreateVector(Pixel.X - Eye.X,Pixel.Y - Eye.Y,Pixel.Z - Eye.Z));

      Ray* rayo = calloc(1, sizeof(rayo));
      rayo->Anchor = Eye;
      //rayo->Direction = Direction;

      PixelColor = GetColor(Direction);

      FrameBuffer[i][j] = PixelColor;
    }
  }
}


Color GetColor(Vector Direction){
  Color color;
  Intersection* intersection;
  double LightIntensity;

  intersection = GetFirstIntersection(Direction);
  if (!intersection->ObjectContainer){
    color =  BACKGROUND;
  }else{
    color = intersection->ObjectContainer->color;
    LightIntensity = GetLightIntensity(Direction, intersection);

    color.RGB.X *= LightIntensity;
    color.RGB.Y *= LightIntensity;
    color.RGB.Z *= LightIntensity;
  }


  return color;
}

Intersection* GetFirstIntersection(Vector Direction){
  int lowerIndex, i;
  Intersection* inter = calloc(1, sizeof(Intersection));
  Node* current = First;
  double minT = DBL_MAX;

  for (i = 0; i < CantObjects; i++) {
    DistanceArray objectTs = GetIntersections(Direction, current->type, current->object);
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

DistanceArray GetIntersections(Vector Direction, ObjectType type ,void* object){
  DistanceArray objectTs = {0, NULL};

  if (type == SPHERE){
    objectTs = ((Sphere*) object)->GetIntersection(((Sphere*) object), Direction);
  }

  return objectTs;
}

double GetLightIntensity(Vector Direction, Intersection* intersection){
  double LightIntensity, t, KD, KA, LDistance, Fatt;
  Vector L,N, Point, DistanceVector;

  t = intersection->t.content[intersection->lowerIndex];

  Point = CreateVector(
    Eye.X + (t * Direction.X),
    Eye.Y + (t * Direction.Y),
    Eye.Z + (t * Direction.Z)
  );

  KD = intersection->ObjectContainer->DiffusionCoefficient;
  KA = intersection->ObjectContainer->AmbientCoefficient;

  if (intersection->ObjectContainer->type == SPHERE){
    N = ((Sphere*) intersection->ObjectContainer->object)->GetNormal(((Sphere*) intersection->ObjectContainer->object), Point);
  }

  for (int i = 0; i < CantLights; i++) {
    DistanceVector = CreateVector(
      Lights[i].Position.X - Point.X,
      Lights[i].Position.Y - Point.Y,
      Lights[i].Position.Z - Point.Z
    );
    LDistance = CalculateNormal(DistanceVector);

    Fatt = 1 / (
      Lights[i].AttenuationC1 +
      (Lights[i].AttenuationC2 * LDistance) +
      (Lights[i].AttenuationC3 * LDistance * LDistance)
    );

    Fatt = (Fatt > 1.0) ? 1.0 : Fatt;

    L = CreateVector(
        (DistanceVector.X) / LDistance,
        (DistanceVector.Y) / LDistance,
        (DistanceVector.Z) / LDistance
    );

    LightIntensity += (
                        PointProduct(L, N) * KD *
                        Lights[i].Intensity * Fatt
                      ) +
                      (AmbientLight * KA);
  }

  LightIntensity = (LightIntensity > 1) ? 1 : LightIntensity;
  LightIntensity = (LightIntensity < 0) ? 0 : LightIntensity;


  return LightIntensity;
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

    fscanf(file, "%s", fileContent);
    Object->DiffusionCoefficient = atof(fileContent);

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

    if (Object->type == SPHERE){
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
