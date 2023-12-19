// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rectangle.h"

class TABLEANDCHAIRS_API Cuboid
{
public:
    Cuboid(FVector origin, FVector size, double angle, int& nsections, UProceduralMeshComponent* mesh, UMaterialInterface* material);
    ~Cuboid();
    void generate();
    void rotate(FVector center, double angle);
    void rotate(double angle);
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

    int m_Counter = 0;
    int& Nsections;

    UProceduralMeshComponent* m_Mesh;   
    UMaterialInterface* m_Material; 
};

