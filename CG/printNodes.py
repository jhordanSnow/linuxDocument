


def printNodes():
    for n in range(3):
        string = ("")
        currNode = "Node* Sphere" , n ,
        prevNode = "Node* Sphere" , n-1
        string = currNode, "= calloc(1, sizeof(Node)); \n"
        string += currNode, "->object = calloc(1, sizeof(Sphere)); \n"
        string += "((Sphere*)" ,currNode,"->object)->Center = CreateVector(20.0, 0.0, 80.0); \n"
        string += "((Sphere*)" ,currNode,"->object)->Radius = 20.0; \n"
        string += "((Sphere*)" ,currNode,"->object)->GetIntersection = &SphereIntersection; \n"
        string += "((Sphere*)" ,currNode,"->object)->GetNormal = &SphereNormal; \n"
        string += currNode,"->color = CreateColor(255.0, 255.0, 0.0, 0.0); \n"
        string += currNode,"->DiffusionCoefficient = 1.0; \n"
        string += currNode,"->AmbientCoefficient = 0.8; \n"
        string += currNode,"->type = SPHERE; \n"
        if(n==0):
            string +="First->next =", currNode,"; \n"
        else:
            string +=  prevNode,"->next =", currNode,"; \n"
        print(string)

def printCaca():
    string = "caca \n"
    string += "caca \n"

printNodes()
