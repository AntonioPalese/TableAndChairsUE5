#include "Chair.h"

Chair::Chair(FVector origin, ChairData::Leg leg, ChairData::Seat seat, ChairData::Back back, double angle, int& nsections, UProceduralMeshComponent* mesh, UMaterialInterface* material)
    : m_Origin(origin), m_Mesh(mesh), Nsections(nsections), m_Material(material)
{
    // legs
    m_Components.Add(new Cuboid(FVector(origin.X - seat.WSeat / 2, origin.Y - seat.LSeat / 2, origin.Z), FVector(leg.WLegs, leg.LLegs, leg.HLegs), angle, Nsections, m_Mesh, m_Material));
    m_Components.Add(new Cuboid(FVector(origin.X + seat.WSeat / 2, origin.Y + seat.LSeat / 2, origin.Z), FVector(leg.WLegs, leg.LLegs, leg.HLegs), angle, Nsections, m_Mesh, m_Material));
    m_Components.Add(new Cuboid(FVector(origin.X + seat.WSeat / 2, origin.Y - seat.LSeat / 2, origin.Z), FVector(leg.WLegs, leg.LLegs, leg.HLegs), angle, Nsections, m_Mesh, m_Material));
    m_Components.Add(new Cuboid(FVector(origin.X - seat.WSeat / 2, origin.Y + seat.LSeat / 2, origin.Z), FVector(leg.WLegs, leg.LLegs, leg.HLegs), angle, Nsections, m_Mesh, m_Material));
  
    // seat
    m_Components.Add(new Cuboid(FVector(origin.X, origin.Y, origin.Z + leg.HLegs / 2 + seat.HSeat / 2), FVector(seat.WSeat + leg.WLegs, seat.LSeat + leg.WLegs, seat.HSeat), angle, Nsections, m_Mesh, m_Material));

    // back
    m_Components.Add(new Cuboid(FVector(origin.X, origin.Y + seat.LSeat / 2, origin.Z + leg.HLegs / 2 + back.HBack / 2), FVector(back.WBack, back.LBack, back.HBack), angle, Nsections, m_Mesh, m_Material));
}

Chair::~Chair()
{
    for (Cuboid* c : m_Components) {
        delete c;
        c = nullptr;
    }
}
/**
     * Procedural generates the chair structure.
**/
void Chair::generate()
{
    for (const auto component : m_Components) {
        component->generate();
    }
}

/**
     * Rotates the chair algong the z axes respect to the center parameter.
     * @param angle : rotation angle
     * @param center : rotation center
**/
void Chair::rotate(FVector center, double angle)
{
    for (const auto component : m_Components) {
        component->rotate(center, angle);
    }
}

/**
     * Rotates the chair algong the z axes respect to the chair origin.
     * @param angle : rotation angle
**/
void Chair::rotate(double angle)
{
    rotate(m_Origin, angle);
}


