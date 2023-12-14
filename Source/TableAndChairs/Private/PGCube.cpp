// Fill out your copyright notice in the Description page of Project Settings.


#include "PGCube.h"
#include <assert.h>

// Sets default values
APGCube::APGCube()
{

	m_Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = m_Mesh;
	m_Mesh->bUseAsyncCooking = true;

}

// This is called when actor is spawned (at runtime or when you drop it into the world in editor)
void APGCube::PostActorCreated()
{
	Super::PostActorCreated();	
	Generate();
}

// This is called when actor is already in level and map is opened
void APGCube::PostLoad()
{
	Super::PostLoad();
	Generate();
}

void APGCube::Generate()
{
	///// chair
	double Hlegs = 60.0;
	double Hback = 80.0;
	double Wseat = 60.0, Lseat = 85.0, Hseat = 5.0;
	double space = 5;	
	////////////////
	
	///// table
	double HlegsTable = 70;
	double Wttop = 400, Lttop = 90, Httop = 10;
	////////////////
	FVector Origin(0.0, 0.0, 0.0);

	assert(HlegsTable - Httop/2 > Hlegs + Hseat/2);

	double rest_lr = Lseat/2 > 5 ? Lseat/2 : 5;
	double N_lr = (Wttop - rest_lr*2) / (Wseat+space);

	double rest_tb = Lseat/2 > 5 ? Lseat/2 : 5;
	double N_tb = (Lttop - rest_tb*2) / (Wseat+space);

	TableGenerate(FVector2D(Origin.X, Origin.Y), HlegsTable, Wttop, Lttop, Httop);

	{
		// Chairs along left		
		double starting_x = Origin.X - N_lr*(Wseat+space)/2 + Wseat/2 + rest_lr;
		double starting_y = Origin.Y + Lttop/2 + Lseat/2;	  
		for (int i = 0; i < N_lr; i++)
		{
			ChairGenerate(FVector2D( starting_x + (Wseat+space)*i, starting_y), Hlegs, Hback, Wseat, Lseat, Hseat, 1);
		}
	}

	{
		// Chairs along right		
		double starting_x = Origin.X - N_lr*(Wseat+space)/2 + Wseat/2  + rest_lr;
		double starting_y = Origin.Y - Lttop/2 - Lseat/2;
		for (int i = 0; i < N_lr; i++)
		{
			ChairGenerate(FVector2D( starting_x + (Wseat+space)*i, starting_y), Hlegs, Hback, Wseat, Lseat, Hseat, -1);
		}
	}

	// double tmp;
	// tmp = Wseat;
	// Wseat = Lseat;
	// Lseat = tmp;

	{
		// Chairs along top
		double starting_y = Origin.Y - N_tb*(Wseat+space)/2 + Wseat/2 + rest_tb;
		double starting_x = Origin.X - Wttop/2 + Lseat/2;
		for (int i = 0; i < N_tb; i++)
		{
			ChairGenerate(FVector2D( starting_x , starting_y + (Wseat+space)*i), Hlegs, Hback, Wseat, Lseat, Hseat, 1);
		}

	}

	{	
		// Chairs along bottom
		double starting_y = Origin.Y - N_tb*(Wseat+space)/2 + Wseat/2 + rest_tb;
		double starting_x = Origin.X + Wttop/2 + Lseat/2;	  
		for (int i = 0; i < N_tb; i++)
		{
			ChairGenerate(FVector2D( starting_x , starting_y + (Wseat+space)*i), Hlegs, Hback, Wseat, Lseat, Hseat, -1);
		}
	}
}

void APGCube::addQuadMesh(FVector TopRight, FVector BottomRight, FVector TopLeft, FVector BottomLeft, int32& TriangleIndexCount, FProcMeshTangent TangentSetup)
{
	int32 Point1 = TriangleIndexCount++;
	int32 Point2 = TriangleIndexCount++;
	int32 Point3 = TriangleIndexCount++;
	int32 Point4 = TriangleIndexCount++;

	Vertices.Add(TopRight);
	Vertices.Add(BottomRight);
	Vertices.Add(TopLeft);
	Vertices.Add(BottomLeft);

	Triangles.Add(Point1);
	Triangles.Add(Point2);
	Triangles.Add(Point3);

	Triangles.Add(Point4);
	Triangles.Add(Point3);
	Triangles.Add(Point2);

	FVector Norm = FVector::CrossProduct(TopLeft - BottomRight, TopLeft - TopRight);
	for (int i = 0; i < 4; i++) {
		Normals.Add(Norm);
		Tangents.Add(TangentSetup);
		Colors.Add(FLinearColor::Green);
	}

	UVs.Add(FVector2D(0.f, 1.f));
	UVs.Add(FVector2D(0.f, 0.f));
	UVs.Add(FVector2D(1.f, 1.f));
	UVs.Add(FVector2D(1.f, 0.f));
}

void APGCube::GenerateMeshes(FVector min, FVector max)
{

	Vertices.Reset();
	Triangles.Reset();
	Normals.Reset();
	UVs.Reset();
	Colors.Reset();
	Tangents.Reset();

	FVector vertexes[8];
	FProcMeshTangent tangent;
	int32 TriangleCounter = 0;


	vertexes[0] = FVector(max.X, max.Y, max.Z);
	vertexes[1] = FVector(max.X, max.Y, min.Z);
	vertexes[2] = FVector(max.X, min.Y, max.Z);
	vertexes[3] = FVector(max.X, min.Y, min.Z);
						  
	vertexes[4] = FVector(min.X, min.Y, max.Z);
	vertexes[5] = FVector(min.X, min.Y, min.Z);
	vertexes[6] = FVector(min.X, max.Y, max.Z);
	vertexes[7] = FVector(min.X, max.Y, min.Z);

	//front
	tangent = FProcMeshTangent(0.f, 1.f, 0.f);
	addQuadMesh(vertexes[0], vertexes[1], vertexes[2], vertexes[3], TriangleCounter, tangent);

	// left
	tangent = FProcMeshTangent(1.f, 0.f, 0.f);
	addQuadMesh(vertexes[2], vertexes[3], vertexes[4], vertexes[5], TriangleCounter, tangent);

	// back
	tangent = FProcMeshTangent(0.f, -1.f, 0.f);
	addQuadMesh(vertexes[4], vertexes[5], vertexes[6], vertexes[7], TriangleCounter, tangent);

	// right
	tangent = FProcMeshTangent(-1.f, 0.f, 0.f);
	addQuadMesh(vertexes[6], vertexes[7], vertexes[0], vertexes[1], TriangleCounter, tangent);

	// top
	tangent = FProcMeshTangent(0.f, 1.f, 0.f);
	addQuadMesh(vertexes[6], vertexes[0], vertexes[4], vertexes[2], TriangleCounter, tangent);

	//bottom
	tangent = FProcMeshTangent(0.f, -1.f, 0.f);
	addQuadMesh(vertexes[1], vertexes[7], vertexes[3], vertexes[5], TriangleCounter, tangent);

	m_Mesh->CreateMeshSection_LinearColor(Nsections++, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);

}

void APGCube::GenerateLeg(FVector2D Origin, FVector2D Ds, double height)
{
	double hd = 5.0;
	for (double i = 0; i < height; i += hd) {
		GenerateMeshes(FVector(Origin.X - Ds.X / 2, Origin.Y - Ds.Y / 2, i), FVector(Origin.X + Ds.X / 2, Origin.Y + Ds.Y / 2, i + hd));
	}
}

void APGCube::GenerateSeat(FVector Origin, FVector Ds)
{	
	GenerateMeshes(FVector(Origin.X - Ds.X / 2, Origin.Y - Ds.Y / 2, Origin.Z - Ds.Z / 2), FVector(Origin.X + Ds.X / 2, Origin.Y + Ds.Y / 2, Origin.Z + Ds.Z / 2));
}

void APGCube::GenerateBack(FVector2D Origin, FVector2D Ds, double starting_height, double height)
{
	double hd = 5.0;
	height += starting_height;
	for (int i = starting_height; i < height; i += hd) {
		GenerateMeshes(FVector(Origin.X - Ds.X / 2, Origin.Y - Ds.Y / 2, i), FVector(Origin.X + Ds.X / 2, Origin.Y + Ds.Y / 2, i + hd));
	}
}

void APGCube::ChairGenerate(FVector2D Origin, double Hlegs, double Hback, double Wseat, double Lseat, double Hseat, int dir)
{
	double shift_x = Wseat/2-5;
	double shift_y = Lseat/2-5;


	// fixed W and L (Legs)
	GenerateLeg(FVector2D(Origin.X - shift_x, Origin.Y - shift_y), FVector2D(5, 5), Hlegs);
	GenerateLeg(FVector2D(Origin.X - shift_x, Origin.Y + shift_y), FVector2D(5, 5), Hlegs);
	GenerateLeg(FVector2D(Origin.X + shift_x, Origin.Y - shift_y), FVector2D(5, 5), Hlegs);
	GenerateLeg(FVector2D(Origin.X + shift_x, Origin.Y + shift_y), FVector2D(5, 5), Hlegs);

	// seat (Seat)
	GenerateSeat(FVector(Origin.X, Origin.Y, Hlegs), FVector(Wseat, Lseat, Hseat));

	// fixed W and L (Back)
	GenerateBack(FVector2D(Origin.X, Origin.Y+(shift_y*dir)), FVector2D(Wseat, 5), Hlegs, Hback);
}

void APGCube::TableGenerate(FVector2D Origin, double Hlegs, double Wttop, double Lttop, double Httop)
{
	/*
	A table is defined as a geometry that has :
	�	A squared tabletop with width, length, and height parameters
	�	4 Legs with a fixed width and length, and a variable height parameter
	*/

	double shift_x = Wttop / 2 - 5;
	double shift_y = Lttop / 2 - 5;

	GenerateLeg(FVector2D(Origin.X - shift_x, Origin.Y - shift_y), FVector2D(5, 5), Hlegs);
	GenerateLeg(FVector2D(Origin.X - shift_x, Origin.Y + shift_y), FVector2D(5, 5), Hlegs);
	GenerateLeg(FVector2D(Origin.X + shift_x, Origin.Y - shift_y), FVector2D(5, 5), Hlegs);
	GenerateLeg(FVector2D(Origin.X + shift_x, Origin.Y + shift_y), FVector2D(5, 5), Hlegs);

	GenerateSeat(FVector(Origin.X, Origin.Y, Hlegs), FVector(Wttop, Lttop, Httop));
}