// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Table.h"
#include "Chair.h"
#include "TableAndChairActor.generated.h"


UCLASS()
class TABLEANDCHAIRS_API ATableAndChairActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATableAndChairActor();

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
	void Generate(FVector Origin);

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* m_Mesh;
private:

	UMaterialInterface* m_Material;
	int32 Nsections = 0;

};
