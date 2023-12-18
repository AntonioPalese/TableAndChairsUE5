#pragma once

#include <vector>
#include <fstream>
#include "Rectangle.h"

class Cuboid{
public:
    Cuboid( FVector origin, FVector size, double angle );
    ~Cuboid();
    void generate();
    Cuboid* rotate( FVector center, double angle );
    Cuboid* rotate( double angle );
private:
    FVector m_Origin;
    FVector m_Size;
    double m_Angle;

    std::vector<Rectangle*> m_Children;
    std::vector<FVector> m_Vertexes;
    std::vector<int> m_Triangles;
    int m_Counter;


    std::ofstream m_Ofs;

};

