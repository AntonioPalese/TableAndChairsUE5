// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "PGCube.generated.h"

UCLASS()
class TABLEANDCHAIRS_API APGCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APGCube();

protected:	

	void PostLoad();
	void PostActorCreated();

	void addQuadMesh(FVector TopRight, FVector BottomRight, FVector TopLeft, FVector BottomLeft, int32& TriangleIndexCount, FProcMeshTangent TangentSetup);
	void GenerateMeshes(FVector min, FVector max);
	void ChairGenerate(FVector2D Origin, int dir);

	void GenerateLeg(FVector2D Origin, FVector2D Ds);
	void GenerateSeat(FVector2D Origin, FVector2D Ds);
	void GenerateBack(FVector2D Origin, FVector2D Ds);

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* m_Mesh;

public:	

private:
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;
	TArray<FProcMeshTangent> Tangents;
	int32 Nsections = 0;	


};
