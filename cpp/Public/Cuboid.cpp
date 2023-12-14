#include "Cuboid.h"
#include "Rectangle.h"

Cuboid::Cuboid(FVector origin, FVector size, double angle)
{
    m_Origin = origin;
    m_Size = size;
    m_Angle = angle;

    double dx = m_Size.X;
    double dy = m_Size.Y;
    double dz = m_Size.Z;

    // top
    m_Children.Add(new Rectangle(FVector(m_Origin.X, m_Origin.Y, m_Origin.Z + dz/2), FVector(dx, dy, 0), "xy", &m_Vertexes, &m_Triangles, m_Counter));
    // back
    m_Children.Add(new Rectangle(FVector(m_Origin.X, m_Origin.Y, m_Origin.Z - dz/2), FVector(dx, dy, 0), "xy", &m_Vertexes, &m_Triangles, m_Counter));
    // front
    m_Children.Add(new Rectangle(FVector(m_Origin.X, m_Origin.Y + dy/2, m_Origin.Z), FVector(dx, 0, dz), "xz", &m_Vertexes, &m_Triangles, m_Counter));
    // bottom
    m_Children.Add(new Rectangle(FVector(m_Origin.X, m_Origin.Y - dy/2, m_Origin.Z), FVector(dx, 0, dz), "xz", &m_Vertexes, &m_Triangles, m_Counter));
    // right
    m_Children.Add(new Rectangle(FVector(m_Origin.X + dx/2, m_Origin.Y, m_Origin.Z), FVector(0, dy, dz), "yz", &m_Vertexes, &m_Triangles, m_Counter));
    // left
    m_Children.Add(new Rectangle(FVector(m_Origin.X - dx/2, m_Origin.Y, m_Origin.Z), FVector(0, dy, dz), "yz", &m_Vertexes, &m_Triangles, m_Counter));
}

void Cuboid::generate()
{
    for(auto& c : m_Children){
        c->draw();
    }
}

Cuboid* Cuboid::rotate( double angle )
{
    return this->rotate(m_Origin, angle);
}

Cuboid* Cuboid::rotate(FVector2D center, double angle )
{
    for(auto& c : m_Children){
        c->rotate(center, angle);
    }
    return this;
}
