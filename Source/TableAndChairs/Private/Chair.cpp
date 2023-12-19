#include "Chair.h"

Chair::Chair(FVector origin, ChairData::Leg leg, ChairData::Seat seat, ChairData::Back back, double angle, int& nsections, UProceduralMeshComponent* mesh, UMaterialInterface* material)
    : m_Origin(origin), m_Mesh(mesh), Nsections(nsections), m_Material(material)
{
    m_Components.Add(new Cuboid(FVector(origin.X - seat.WSeat / 2, origin.Y - seat.LSeat / 2, origin.Z), FVector(leg.WLegs, leg.LLegs, leg.HLegs), angle, Nsections, m_Mesh, m_Material));
    m_Components.Add(new Cuboid(FVector(origin.X + seat.WSeat / 2, origin.Y + seat.LSeat / 2, origin.Z), FVector(leg.WLegs, leg.LLegs, leg.HLegs), angle, Nsections, m_Mesh, m_Material));
    m_Components.Add(new Cuboid(FVector(origin.X + seat.WSeat / 2, origin.Y - seat.LSeat / 2, origin.Z), FVector(leg.WLegs, leg.LLegs, leg.HLegs), angle, Nsections, m_Mesh, m_Material));
    m_Components.Add(new Cuboid(FVector(origin.X - seat.WSeat / 2, origin.Y + seat.LSeat / 2, origin.Z), FVector(leg.WLegs, leg.LLegs, leg.HLegs), angle, Nsections, m_Mesh, m_Material));
                
    m_Components.Add(new Cuboid(FVector(origin.X, origin.Y, origin.Z + leg.HLegs / 2 + seat.HSeat / 2), FVector(seat.WSeat + leg.WLegs, seat.LSeat + leg.WLegs, seat.HSeat), angle, Nsections, m_Mesh, m_Material));
                 
    m_Components.Add(new Cuboid(FVector(origin.X, origin.Y + seat.LSeat / 2, origin.Z + leg.HLegs / 2 + back.HBack / 2), FVector(back.WBack, back.LBack, back.HBack), angle, Nsections, m_Mesh, m_Material));
}

Chair::~Chair()
{
    for (Cuboid* c : m_Components) {
        delete c;
        c = nullptr;
    }
}

void Chair::generate()
{
    for (const auto component : m_Components) {
        component->generate();
    }
}

void Chair::rotate(FVector center, double angle)
{
    for (const auto component : m_Components) {
        component->rotate(center, angle);
    }
}

void Chair::rotate(double angle)
{
    rotate(m_Origin, angle);
}


