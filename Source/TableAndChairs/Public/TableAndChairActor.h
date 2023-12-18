// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cuboid.h"
#include "Rectangle.h"
#include "TableAndChairActor.generated.h"


UCLASS()
class TABLEANDCHAIRS_API ATableAndChairActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATableAndChairActor();

protected:

	void PostLoad();
	void PostActorCreated();

public:	
	void Generate(FVector Origin);



	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* m_Mesh;
private:

	UMaterialInterface* m_Material;
	int32 Nsections = 0;

};
