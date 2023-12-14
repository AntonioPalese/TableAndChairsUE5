#pragma once
#include <vector>
#include <iostream>
#include <string>

class FVector {
public:
    FVector() : X( 0 ), Y( 0 ), Z( 0 ) {}
    FVector( double x, double y, double z ) : X( x ), Y( y ), Z( z ) {}
    double X, Y, Z;

};

class FVector2D {
public:
    FVector2D() : X( 0 ), Y( 0 ) {}
    FVector2D( double x, double y) : X( x ), Y( y ) {}
    double X, Y;
};

namespace utils {
    FVector rotate( FVector P, double angle );
}

class Rectangle {
public:
    Rectangle( FVector origin, FVector size, double angle, std::string mode, std::vector<FVector>& vertexes, std::vector<int>& triangles, int& counter );

    Rectangle* rotate( FVector center, double angle );
    Rectangle* rotate( double angle );
    // void draw();
    // void _mesh();
private:
    FVector m_Origin;
    FVector m_Size;
    double m_Angle;

    std::vector<FVector>& m_Vertexes;
    std::vector<Rectangle*> m_Children;
    std::vector<int>& m_Triangles;
    std::vector<int> m_Indexes;
};