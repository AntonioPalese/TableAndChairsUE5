#include "Cuboid.h"
#include <iostream>

Cuboid::Cuboid( FVector origin, FVector size, double angle )
{
    m_Origin = origin;
    m_Size = size;
    m_Angle = angle;

    double dx = m_Size.X;
    double dy = m_Size.Y;
    double dz = m_Size.Z;

    // top
    m_Children.push_back( new Rectangle( FVector( m_Origin.X, m_Origin.Y, m_Origin.Z + dz / 2 ), FVector( dx, dy, 0 ), 0.0, "xy", m_Vertexes, m_Triangles, m_Counter ) );
    // back                                                                                                             
    m_Children.push_back( new Rectangle( FVector( m_Origin.X, m_Origin.Y, m_Origin.Z - dz / 2 ), FVector( dx, dy, 0 ), 0.0, "xy", m_Vertexes, m_Triangles, m_Counter ) );
    // front                                                                                                           
    m_Children.push_back( new Rectangle( FVector( m_Origin.X, m_Origin.Y + dy / 2, m_Origin.Z ), FVector( dx, 0, dz ), 0.0, "xz", m_Vertexes, m_Triangles, m_Counter ) );
    // bottom                                                                                                           
    m_Children.push_back( new Rectangle( FVector( m_Origin.X, m_Origin.Y - dy / 2, m_Origin.Z ), FVector( dx, 0, dz ), 0.0, "xz", m_Vertexes, m_Triangles, m_Counter ) );
    // right                                                                                                            
    m_Children.push_back( new Rectangle( FVector( m_Origin.X + dx / 2, m_Origin.Y, m_Origin.Z ), FVector( 0, dy, dz ), 0.0, "yz", m_Vertexes, m_Triangles, m_Counter ) );
    // left                                                                                                             
    m_Children.push_back( new Rectangle( FVector( m_Origin.X - dx / 2, m_Origin.Y, m_Origin.Z ), FVector( 0, dy, dz ), 0.0, "yz", m_Vertexes, m_Triangles, m_Counter ) );
}

Cuboid::~Cuboid()
{
    for ( Rectangle* c : m_Children ) {
        delete c;
        c = nullptr;
    }
}

std::ostream& operator<<( std::ostream& os, const FVector& vec )
{
    return os << "(" << vec.X << "," << vec.Y << "," << vec.Z << ")";
}

void Cuboid::generate()
{
    for ( const auto& v : m_Vertexes ) {
        std::cout << v << "::";
    }
    std::cout << std::endl;

    for ( const auto& t : m_Triangles ) {
        std::cout << t << ",";
    }
    std::cout << std::endl;
}

Cuboid* Cuboid::rotate( double angle )
{
    return this->rotate( m_Origin, angle );
}

Cuboid* Cuboid::rotate( FVector center, double angle )
{
    for ( auto c : m_Children ) {
        c->rotate( center, angle );
    }
    return this;
}
