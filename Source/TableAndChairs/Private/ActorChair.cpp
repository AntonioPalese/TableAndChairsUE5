// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorChair.h"

// Sets default values
AActorChair::AActorChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorChair::BeginPlay()
{
	Super::BeginPlay();
	printf("Called Printf");
	
}

// Called every frame
void AActorChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

