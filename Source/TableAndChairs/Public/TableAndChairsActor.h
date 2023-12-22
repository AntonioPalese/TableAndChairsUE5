// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Chair.h"
#include "Table.h"
#include "TableAndChairsActor.generated.h"

UCLASS()
class TABLEANDCHAIRS_API ATableAndChairsActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATableAndChairsActor();

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
	void Regenerate();

protected:

	void PostLoad();
	void PostActorCreated();

public:
	void Generate(FVector Origin);

	void ChairGenerate(FVector2D Origin, double angle);
	void TableGenerate(FVector2D Origin, double angle);

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* m_Mesh;
private:

	UMaterialInterface* m_Chairs_Material;
	UMaterialInterface* m_Table_Material;
	int32 Nsections = 0;
	double m_Legs_W;
	double m_Legs_L;

};
