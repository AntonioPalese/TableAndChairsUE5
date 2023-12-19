// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Cuboid.h"
#include "ProceduralMeshComponent.h"
#include "CoreMinimal.h"

struct ChairData {
    struct Leg {
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

class TABLEANDCHAIRS_API Chair
{
public:
    Chair(FVector origin, ChairData::Leg leg, ChairData::Seat seat, ChairData::Back back, double angle, int& nsections, UProceduralMeshComponent* mesh, UMaterialInterface* material);
    ~Chair();
    void generate();
    void rotate(FVector center, double angle);
    void rotate(double angle);
private:
    TArray<Cuboid*> m_Components;
    UProceduralMeshComponent* m_Mesh;
    FVector m_Origin;
    UMaterialInterface* m_Material;

    int& Nsections;
};

