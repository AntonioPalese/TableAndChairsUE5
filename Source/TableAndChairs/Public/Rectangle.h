// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"

namespace utils {
    FVector rotate(FVector P, double angle);
}

class TABLEANDCHAIRS_API Rectangle
{
public:
    Rectangle(FVector origin, FVector size, double angle, FString mode, TArray<FVector>& vertexes, TArray<int>& triangles, TArray<FVector>& normals, TArray<FProcMeshTangent>& tangents, TArray<FVector2D>& uvs, int& counter, bool clockwise = true);

    void rotate(FVector center, double angle);
    void rotate(double angle);
private:
    FVector m_Origin;
    FVector m_Size;
    double m_Angle;

    TArray<FVector>& m_Vertexes;
    TArray<int>& m_Triangles;
    TArray<int> m_Indexes;
    TArray<FVector2D>& m_UVs;
    TArray<FVector>& m_Normals;
    TArray<FProcMeshTangent>& m_Tangents;
};