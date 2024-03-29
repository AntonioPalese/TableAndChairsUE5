#pragma once
#include "Cuboid.h"


struct TableData {    
    struct Leg{
        double WLegs, LLegs, HLegs;
    };
    struct Top
    {
        double WTop, LTop, HTop;
    };   
};

class Table
{
public:
    Table(FVector origin, TableData::Leg leg, TableData::Top top, double angle, int nsections, UProceduralMeshComponent* mesh);
    ~Table();
    void generate();
    void rotate( FVector center, double angle );
    void rotate( double angle );
private:
    TArray<Cuboid*> m_Components;
    UProceduralMeshComponent* m_Mesh;
    FVector m_Origin;
    
    int Nsections;
};

