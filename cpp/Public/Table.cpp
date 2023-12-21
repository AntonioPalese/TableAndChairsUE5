#include "Table.h"

Table::Table( FVector origin, TableData::Leg leg, TableData::Top top, double angle, UProceduralMeshComponent* mesh ) : m_Origin( origin ), m_Mesh(mesh), Nsections(nsections)
{
    m_Components.push_back( new Cuboid( FVector( origin.X - top.WTop / 2, origin.Y - top.LTop / 2, origin.Z ), FVector( leg.WLegs, leg.LLegs, leg.HLegs ), angle, Nsections, m_Mesh) );
    m_Components.push_back( new Cuboid( FVector( origin.X + top.WTop / 2, origin.Y + top.LTop / 2, origin.Z ), FVector( leg.WLegs, leg.LLegs, leg.HLegs ), angle, Nsections, m_Mesh) );
    m_Components.push_back( new Cuboid( FVector( origin.X + top.WTop / 2, origin.Y - top.LTop / 2, origin.Z ), FVector( leg.WLegs, leg.LLegs, leg.HLegs ), angle, Nsections, m_Mesh) );
    m_Components.push_back( new Cuboid( FVector( origin.X - top.WTop / 2, origin.Y + top.LTop / 2, origin.Z ), FVector( leg.WLegs, leg.LLegs, leg.HLegs ), angle, Nsections, m_Mesh) );

    m_Components.push_back( new Cuboid( FVector( origin.X, origin.Y, origin.Z + leg.HLegs / 2 + top.HTop / 2 ), FVector( top.WTop + leg.WLegs, top.LTop + leg.WLegs, top.HTop ), angle, Nsections, m_Mesh) );
}

Table::~Table()
{
    for ( Cuboid* c : m_Components ) {
        delete c;
        c = nullptr;
    }
}

void Table::generate()
{
    for ( const auto component : m_Components ) {
        component->generate();
    }
}

void Table::rotate( FVector center, double angle )
{
    for ( const auto component : m_Components ) {
        component->rotate( center, angle );
    }
}

void Table::rotate( double angle )
{
    rotate( m_Origin, angle );
}


