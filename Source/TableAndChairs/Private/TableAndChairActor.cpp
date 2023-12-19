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
	//assert(HlegsTable - Httop/2 > Hlegs + Hseat/2);
	//assert(Lttop > Lseat);

	double rest_lr = Lseat/2 > 5 ? Lseat/2 : 5;
	int N_lr = floor((Wttop - rest_lr * 2) / (Wseat + Space));

	double rest_tb = 5;
	int N_tb = floor((Lttop - rest_tb*2) / (Wseat+ Space));

	TableGenerate(FVector2D(Origin.X, Origin.Y), 0.0);

	{
		// Chairs along left		
		double compensation = ((Wttop - rest_lr * 2) - N_lr * (Wseat + Space)) / 2;
		double starting_x = Origin.X + Wttop/2 - rest_lr -Wseat / 2 - compensation;
		double starting_y = Origin.Y + Lttop / 2;
		for (int i = 0; i < N_lr; i++)
		{
			ChairGenerate(FVector2D( starting_x - (Wseat+ Space)*i, starting_y), 0.0);
		}
	}

	{
		// Chairs along right		
		double compensation = ((Wttop - rest_lr * 2) - N_lr * (Wseat + Space)) / 2;
		double starting_x = Origin.X + Wttop / 2 - rest_lr - Wseat / 2 - compensation;
		double starting_y = Origin.Y - Lttop / 2;
		for (int i = 0; i < N_lr; i++)
		{
			ChairGenerate(FVector2D( starting_x - (Wseat+ Space)*i, starting_y), 180.0);
		}
	}

	{
		// Chairs along top
		double compensation = ((Lttop - rest_tb * 2) - N_tb * (Wseat + Space)) / 2;
		double starting_x = Origin.X + Wttop / 2;
		double starting_y = Origin.Y - Lttop / 2 + rest_tb + Wseat / 2 + compensation;
		for (int i = 0; i < N_tb; i++)
		{
			ChairGenerate(FVector2D(starting_x , starting_y + (Wseat + Space) * i), 90.0);
		}

	}

	{	
		// Chairs along bottom
		double compensation = ((Lttop - rest_tb * 2) - N_tb * (Wseat + Space)) / 2;
		double starting_x = Origin.X - Wttop / 2;
		double starting_y = Origin.Y - Lttop / 2 + rest_tb + Wseat / 2 + compensation;
		for (int i = 0; i < N_tb; i++)
		{
			ChairGenerate(FVector2D(starting_x , starting_y + (Wseat + Space) * i), 270.0);
		}
	}
}

void ATableAndChairActor::Regenerate()
{
	for (int i = 0; i < Nsections; i++) {
		m_Mesh->ClearMeshSection(i);
	}
	Nsections = 0;
	Generate(FVector(0.0, 0.0, 0.0));
}


void ATableAndChairActor::ChairGenerate(FVector2D Origin, double angle)
{
	Chair ch(FVector(Origin.X, Origin.Y, 0.0), ChairData::Leg{5.0, 5.0, Hlegs}, Chair::Seat{Wseat, Lseat, Hseat}, ChairData::Back{Wseat, 5.0, Hback}, 0.0, Nsections, m_Mesh, m_Material);

	if (angle != 0.0)
		ch.rotate(angle);
	
	ch.generate();
}

void ATableAndChairActor::TableGenerate(FVector2D Origin, double angle)
{
	Table t(FVector(Origin.X, Origin.Y, 0.0), TableData::Leg{5.0, 5.0, HTlegs}, TableData::Top{Wttop, Lttop, Httop}, 0.0, Nsections, m_Mesh, m_Material);

	if (angle != 0.0)
		t.rotate(angle);
	
	t.generate();
}
