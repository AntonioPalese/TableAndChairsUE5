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

	/// table
	HTlegs = FMath::RandRange(80.0, 120.0);
	Wttop = FMath::RandRange(200, 800);
	Lttop = FMath::RandRange(200, 800);
	Httop = FMath::RandRange(10.0, 30.0);
	//////////////

	/// chair
	Wseat = FMath::RandRange(30, 120);
	Lseat = FMath::RandRange(30, 120);
	Hseat = FMath::RandRange(5.0, 20.0);
	Hlegs = FMath::RandRange(60.0, (HTlegs - HTlegs/3) - Hseat);
	Hback = FMath::RandRange(30.0, 100.0);
	//////////////

	// Hardcoded Parameters
	m_Legs_L = 5.0;
	m_Legs_W = 5.0;
	

	Space = FMath::RandRange(5.0, Wseat);
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
	// Priority is given to generate along left / right sides
	double rest_lr = Lseat/2 > m_Legs_L ? Lseat/2 : m_Legs_L;	
	// number of feasible chairs on left / right sides 
	int N_lr = int(floor((Wttop - rest_lr * 2) / (Wseat + Space)));

	// Along top / bottom sides, chairs are generated only if they don't collide with left / right ones (according to Space)
	double rest_tb = m_Legs_L;
	// number of feasible chairs on tob / bottom sides 
	int N_tb = int(floor((Lttop - rest_tb * 2) / (Wseat + Space)));

	TableGenerate(FVector2D(Origin.X, Origin.Y), 0.0);

	{
		// Chairs along left / right	
		// compensation needed for centering
		double compensation = (space + (Wttop - rest_lr * 2) % (Wseat + Space)) / 2;
		double starting_x = Origin.X + Wttop / 2 - rest_lr - Wseat / 2 - compensation;
		double starting_y_l = Origin.Y + Lttop / 2;
		double starting_y_r = Origin.Y - Lttop / 2;

		for (int i = 0; i < N_lr; i++)
		{
			ChairGenerate(FVector2D( starting_x - (Wseat+ Space) * i, starting_y_l), 0.0);
			ChairGenerate(FVector2D( starting_x - (Wseat+ Space) * i, starting_y_r), 180.0);
		}		
	}

	{
		// Chairs along top / bottom	
		// compensation needed for centering
		double compensation = (space + (Lttop - rest_lr * 2) % (Wseat + Space)) / 2;
		double starting_x_t = Origin.X + Wttop / 2;
		double starting_x_b = Origin.X - Wttop / 2;
		double starting_y = Origin.Y - Lttop / 2 + rest_tb + Wseat / 2 + compensation;	

		for (int i = 0; i < N_tb; i++)
		{
			ChairGenerate(FVector2D(starting_x_t , starting_y + (Wseat + Space) * i), 270.0);
			ChairGenerate(FVector2D(starting_x_b , starting_y + (Wseat + Space) * i), 90.0);
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
	Chair ch(FVector(Origin.X, Origin.Y, Hlegs/2), ChairData::Leg{m_Legs_W, m_Legs_L, Hlegs}, ChairData::Seat{Wseat, Lseat, Hseat}, ChairData::Back{Wseat, m_Legs_L, Hback}, 0.0, Nsections, m_Mesh, m_Material);

	if (angle != 0.0)
		ch.rotate(angle);
	
	ch.generate();
}

void ATableAndChairActor::TableGenerate(FVector2D Origin, double angle)
{
	Table t(FVector(Origin.X, Origin.Y, HTlegs/2), TableData::Leg{m_Legs_W, m_Legs_L, HTlegs}, TableData::Top{Wttop, Lttop, Httop}, 0.0, Nsections, m_Mesh, m_Material);

	if (angle != 0.0)
		t.rotate(angle);
	
	t.generate();
}
