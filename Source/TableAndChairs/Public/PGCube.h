// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Engine/GameEngine.h"
#include "PGCube.generated.h"


UCLASS(Blueprintable)
class TABLEANDCHAIRS_API APGCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APGCube();


	UPROPERTY(BlueprintReadWrite)
	double Wseat;
	UPROPERTY(BlueprintReadWrite)
	double Lseat;
	UPROPERTY(BlueprintReadWrite)
	double Hseat;

	UFUNCTION(BlueprintCallable)
	void ReGenerate();

	//UFUNCTION(BlueprintCallable)
	//void Remove();

protected:	

	void PostLoad();
	void PostActorCreated();

	void addQuadMesh(FVector TopRight, FVector BottomRight, FVector TopLeft, FVector BottomLeft, int32& TriangleIndexCount, FProcMeshTangent TangentSetup);
	void GenerateMeshes(FVector min, FVector max);
	void ChairGenerate(FVector2D Origin, double Hlegs, double Hback, int dir = 1, bool rotated = false);
	void TableGenerate(FVector2D Origin, double Hlegs, double Wttop, double Lttop, double Httop);
	void Generate(FVector Origin);

	void GenerateLeg(FVector2D Origin, FVector2D Ds, double height);
	void GenerateSeat(FVector Origin, FVector Ds);
	void GenerateBack(FVector2D Origin, FVector2D Ds, double starting_height, double height);

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
