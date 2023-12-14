#include "Rectangle.h"
#include <assert.h>

FVector utils::rotate(FVector P, double angle)
{
    return FVector(P.X*math.cos(math.radians(angle)) - P.Y*math.sin(math.radians(angle)), P.X*math.sin(math.radians(angle)) + P.Y*math.cos(math.radians(angle)), P.Z);
}

Rectangle::Rectangle(FVector origin, FVector size, double angle, FString mode, TArray<FVector>* vertexes,  TArray<FVector>* triangles, int32& counter)
{
    TArray<FString> modes{FString("xy"), FString("xz"), FString("yz")};
    assert( modes.find(mode) != modes.end() );

    m_Origin = origin;
    m_Size = size;
    m_Angle = angle;

    m_Vertexes = vertexes;
    m_Triangles = triangles;

    double dx = m_Size.X / 2;
    double dy = m_Size.Y / 2;
    double dz = m_Size.Z / 2;
    
    FVector p0, p1, p2, p3;    
    if (mode == "xy"){
        p0 = FVector(m_Origin.X - dx, m_Origin.Y - dy, m_Origin.Z);
        p1 = FVector(m_Origin.X + dx, m_Origin.Y - dy, m_Origin.Z);
        p2 = FVector(m_Origin.X + dx, m_Origin.Y + dy, m_Origin.Z);
        p3 = FVector(m_Origin.X - dx, m_Origin.Y + dy, m_Origin.Z);
    }else if(mode == "xz"){
        p0 = FVector(m_Origin.X - dx, m_Origin.Y, m_Origin.Z - dz);
        p1 = FVector(m_Origin.X + dx, m_Origin.Y, m_Origin.Z - dz);
        p2 = FVector(m_Origin.X + dx, m_Origin.Y, m_Origin.Z + dz);
        p3 = FVector(m_Origin.X - dx, m_Origin.Y, m_Origin.Z + dz);
    }else if(mode == "yz"){
        p0 = FVector(m_Origin.X, m_Origin.Y - dy, m_Origin.Z - dz);
        p1 = FVector(m_Origin.X, m_Origin.Y - dy, m_Origin.Z + dz);
        p2 = FVector(m_Origin.X, m_Origin.Y + dy, m_Origin.Z + dz);
        p3 = FVector(m_Origin.X, m_Origin.Y + dy, m_Origin.Z - dz);
    }

    int Point1 = counter++;
    int Point2 = counter++;
    int Point3 = counter++;
    int Point4 = counter++;

    m_Vertexes->Add(p0);
    m_Vertexes->Add(p1);
    m_Vertexes->Add(p2);
    m_Vertexes->Add(p3);

    if (m_Angle != 0.0){
        this->rotate(m_Angle)
    }

    m_Triangles->Add(Point1);
    m_Triangles->Add(Point2);
    m_Triangles->Add(Point3);

    m_Triangles->Add(Point1);
    m_Triangles->Add(Point3);
    m_Triangles->Add(Point4);

    m_Indexes.Add(Point1);
    m_Indexes.Add(Point2);
    m_Indexes.Add(Point3);
    m_Indexes.Add(Point4);
}

Rectangle* Rectangle::rotate(FVector2D center, double angle)
{
    FVector p0 = *(m_Vertexes)[m_Indexes[0]];
    FVector p1 = *(m_Vertexes)[m_Indexes[1]];
    FVector p2 = *(m_Vertexes)[m_Indexes[2]];
    FVector p3 = *(m_Vertexes)[m_Indexes[3]];
    
    p0 = FVector(p0.X - center.X, p0.Y - center.Y, p0.Z);
    p1 = FVector(p1.X - center.X, p1.Y - center.Y, p1.Z);
    p2 = FVector(p2.X - center.X, p2.Y - center.Y, p2.Z);
    p3 = FVector(p3.X - center.X, p3.Y - center.Y, p3.Z);

    p0 = utils::rotate(p0, angle);
    p1 = utils::rotate(p1, angle);
    p2 = utils::rotate(p2, angle);
    p3 = utils::rotate(p3, angle);

    p0 = FVector(p0.X + center.X, p0.Y + center.Y, p0.Z);
    p1 = FVector(p1.X + center.X, p1.Y + center.Y, p1.Z);
    p2 = FVector(p2.X + center.X, p2.Y + center.Y, p2.Z);
    p3 = FVector(p3.X + center.X, p3.Y + center.Y, p3.Z);

    *(m_Vertexes)[m_Indexes[0]] = p0;
    *(m_Vertexes)[m_Indexes[1]] = p1;
    *(m_Vertexes)[m_Indexes[2]] = p2;
    *(m_Vertexes)[m_Indexes[3]] = p3;

    for(auto& c : m_Children){
        c->rotate(center, angle);
    }

    return this;
}

Rectangle* Rectangle::rotate(double angle)
{
    return this->rotate(m_Origin, angle);    
}

// void Rectangle::draw()
// {
//     for(auto& c : m_Children){
//         c->draw();
//     }

//     this->_mesh();
// }
// void Rectangle::_mesh(){
//     // UProceduralMeshComponent
// }
