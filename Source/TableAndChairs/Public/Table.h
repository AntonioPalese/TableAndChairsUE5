// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cuboid.h"
#include "CoreMinimal.h"

struct TableData {
    struct Leg {
        double WLegs, LLegs, HLegs;
    };
    struct Top
    {
        double WTop, LTop, HTop;
    };
};

class TABLEANDCHAIRS_API Table
{
public:
    Table(FVector origin, TableData::Leg leg, TableData::Top top, double angle, int& nsections, UProceduralMeshComponent* mesh, UMaterialInterface* material);
    ~Table();
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
