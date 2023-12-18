#pragma once
#include <iostream>
#include <string>

namespace utils {
    FVector rotate( FVector P, double angle );
}

class Rectangle {
public:
    Rectangle( FVector origin, FVector size, double angle, std::string mode, TArray<FVector>& vertexes, TArray<int>& triangles,  TArray<FVector2D>& normals,  TArray<FVector2D>& uvs, int& counter );

    void rotate( FVector center, double angle );
    void rotate( double angle );
private:
    FVector m_Origin;
    FVector m_Size;
    double m_Angle;

    TArray<FVector>& m_Vertexes;
    TArray<Rectangle*> m_Children;
    TArray<int>& m_Triangles;
    TArray<int> m_Indexes;
    TArray<FVector2D> m_UVs;
    TArray<FVector> m_Normals;
    TArray<FProcMeshTangent> m_Tangents;
};