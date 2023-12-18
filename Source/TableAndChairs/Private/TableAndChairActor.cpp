// Fill out your copyright notice in the Description page of Project Settings.


#include "TableAndChairActor.h"

// Sets default values
ATableAndChairActor::ATableAndChairActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	m_Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = m_Mesh;
	m_Mesh->bUseAsyncCooking = true;
	m_Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	m_Mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	m_Mesh->SetGenerateOverlapEvents(true);
	m_Mesh->SetNotifyRigidBodyCollision(true);
	m_Mesh->bUseComplexAsSimpleCollision = false;


	ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("/Script/Engine.Material'/Game/Textures/brown_leather_albedo_4k_Mat.brown_leather_albedo_4k_Mat'"));
	m_Material = Material.Object.Get();

}

// This is called when actor is spawned (at runtime or when you drop it into the world in editor)
void ATableAndChairActor::PostActorCreated()
{
	Super::PostActorCreated();
	Generate(FVector(0.0, 0.0, 0.0));

}

// This is called when actor is already in level and map is opened
void ATableAndChairActor::PostLoad()
{
	Super::PostLoad();
	Generate(FVector(0.0, 0.0, 0.0));
}

void ATableAndChairActor::Generate(FVector Origin)
{
	TArray<FVector> m_Vertexes;
	TArray<int> m_Triangles;
	TArray<FVector2D> m_UVs;
	TArray<FVector> m_Normals;
	TArray<FProcMeshTangent> m_Tangents;
	TArray<FLinearColor> Colors;
	int m_Counter = 0;

	for (int i = 0; i < 24; i++) {
		Colors.Add(FLinearColor::Green);
	}

	// top
	for(int i = 0; i < 4; i++){
		m_Normals.Add(FVector(0.0, 0.0, 1.0));
		m_Tangents.Add(FProcMeshTangent(0.0, 1.0, 0.0));
	}
	Rectangle top(FVector(0.0, 0.0, 50.0), FVector(100.0, 100.0, 0.0), 0.0, "xy", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, true);

	// bottom
	for (int i = 0; i < 4; i++) {
		m_Normals.Add(FVector(0.0, 0.0, -1.0));
		m_Tangents.Add(FProcMeshTangent(0.0, -1.0, 0.0));
	}
	Rectangle bottom(FVector(0.0, 0.0, -50.0), FVector(100.0, 100.0, 0.0), 0.0, "xy", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, false);

	// back
	for (int i = 0; i < 4; i++) {
		m_Normals.Add(FVector(1.0, 0.0, 0.0));
		m_Tangents.Add(FProcMeshTangent(0.0, 1.0, 0.0));
	}
	Rectangle back(FVector(50.0, 0.0, 0.0), FVector(0.0, 100.0, 100.0), 0.0, "yz", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, false);


	// front
	for (int i = 0; i < 4; i++) {
		m_Normals.Add(FVector(-1.0, 0.0, 0.0));
		m_Tangents.Add(FProcMeshTangent(0.0, -1.0, 0.0));
	}
	Rectangle front(FVector(-50.0, 0.0, 0.0), FVector(0.0, 100.0, 100.0), 0.0, "yz", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, true);

	// left
	for (int i = 0; i < 4; i++) {
		m_Normals.Add(FVector(0.0, 1.0, 0.0));
		m_Tangents.Add(FProcMeshTangent(0.0, 0.0, 1.0));
	}
	Rectangle left(FVector(0.0, 50.0, 0.0), FVector(100.0, 0.0, 100.0), 0.0, "xz", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, false);

	// right
	for (int i = 0; i < 4; i++) {
		m_Normals.Add(FVector(0.0, -1.0, 0.0));
		m_Tangents.Add(FProcMeshTangent(0.0, 0.0, -1.0));
	}
	Rectangle right(FVector(0.0, -50.0, 0.0), FVector(100.0, 0.0, 100.0), 0.0, "xz", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, true);


	
	m_Mesh->SetMaterial(0, m_Material);
	m_Mesh->CreateMeshSection_LinearColor(0, m_Vertexes, m_Triangles, m_Normals, m_UVs, Colors, m_Tangents, true);

}

