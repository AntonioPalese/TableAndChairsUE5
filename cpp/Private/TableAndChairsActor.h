// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Engine/GameEngine.h"
#include "Chair.h"
#include "Table.h"
#include "PGCube.generated.h"


UCLASS(Blueprintable)
class TABLEANDCHAIRS_API TableAndChairs : public AActor
{
	GENERATED_BODY()
	
public:	
	TableAndChairs();

	// chair
	UPROPERTY(BlueprintReadWrite)
	double Wseat;
	UPROPERTY(BlueprintReadWrite)
	double Lseat;
	UPROPERTY(BlueprintReadWrite)
	double Hseat;

	UPROPERTY(BlueprintReadWrite)
	double Hlegs;
	UPROPERTY(BlueprintReadWrite)
	double Hback;

	// table
	UPROPERTY(BlueprintReadWrite)
	double Httop;
	UPROPERTY(BlueprintReadWrite)
	double Wttop;
	UPROPERTY(BlueprintReadWrite)
	double Lttop;
	UPROPERTY(BlueprintReadWrite)
	double HTlegs;

	UPROPERTY(BlueprintReadWrite)
	double Space;

	UFUNCTION(BlueprintCallable)
	void ReGenerate();


protected:	

	void PostLoad();
	void PostActorCreated();

	void ChairGenerate(FVector2D Origin, double angle);
	void TableGenerate(FVector2D Origin, double angle);
	void Generate(FVector Origin);

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* m_Mesh;

private:
	int32 Nsections = 0;
};
