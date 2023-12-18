#pragma once

#include <vector>
#include <fstream>
#include "Rectangle.h"

class Cuboid{
public:
    Cuboid( FVector origin, FVector size, double angle, int nsections, UProceduralMeshComponent* mesh);
    ~Cuboid();
    void generate();
    void rotate( FVector center, double angle );
    void rotate( double angle );
private:
    FVector m_Origin;
    FVector m_Size;
    double m_Angle;

    TArray<Rectangle*> m_Children;
    TArray<FVector> m_Vertexes;
    TArray<int> m_Triangles;
    TArray<FVector2D> m_UVs;
    TArray<FVector> m_Normals;
    TArray<FProcMeshTangent> m_Tangents;

    int m_Counter;
    int& Nsections;

    UProceduralMeshComponent* m_Mesh;
    ConstructorHelpers::FObjectFinder<UMaterialInterface> m_Material(TEXT("/Script/Engine.Material'/Game/Textures/brown_leather_albedo_4k_Mat.brown_leather_albedo_4k_Mat'"));
};

