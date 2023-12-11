// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "MyActor.generated.h"


UCLASS()
class TABLEANDCHAIRS_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	AMyActor();

protected:
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	FVector ComputeFaceNormal(const FVector& A, const FVector& B, const FVector& C);
	void ComputeVertexNormals();
	void GetTangentFromNormal();
	void CalculateUVs();
	void GenerateMesh();

public:
	void AddQuad(TArray<double> Idx1, TArray<double> Idx2);

	void CreateChair();

protected:
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* m_Mesh;

	UPROPERTY(EditAnywhere)
	int32 x = 100;
	UPROPERTY(EditAnywhere)
	int32 y = 100;
	UPROPERTY(EditAnywhere)
	int32 z = 100;
private:
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;
	TArray<FProcMeshTangent> Tangents;

};
