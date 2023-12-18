#pragma once
#include "Cuboid.h"


struct ChairData {    
    struct Leg{
        double WLegs, LLegs, HLegs;
    };
    struct Seat
    {
        double WSeat, LSeat, HSeat;
    };
    struct Back
    {
        double WBack, LBack, HBack;
    };    
};

class Chair
{
public:
    Chair(FVector origin, ChairData::Leg leg, ChairData::Seat seat, ChairData::Back back, double angle, int nsections, UProceduralMeshComponent* mesh);
    ~Chair();
    void generate();
    void rotate( FVector center, double angle );
    void rotate( double angle );
private:
    TArray<Cuboid*> m_Components;
    UProceduralMeshComponent* m_Mesh;
    FVector m_Origin;
    
    int Nsections;
};

