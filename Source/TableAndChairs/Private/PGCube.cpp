// Fill out your copyright notice in the Description page of Project Settings.


#include "PGCube.h"

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
	double Hlegs = 60.0;
	double Hback = 80.0;
	double Wseat = 30.0, Lseat = 40.0, Hseat = 5.0;
	double space_along_y = 120;
	double space = 40;

	//Wseat along x, Lseat along y
	for (int i = 0; i < 2; i++)
	{
		ChairGenerate(FVector2D( (Wseat + space) * i, 0), Hlegs, Hback, Wseat, Lseat, Hseat, 1);
		ChairGenerate(FVector2D( (Wseat + space) * i, -space_along_y), Hlegs, Hback, Wseat, Lseat, Hseat, -1);
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
	int shift = 15;


	// fixed W and L (Legs)
	GenerateLeg(FVector2D(Origin.X - shift, Origin.Y - shift), FVector2D(5, 5), Hlegs);
	GenerateLeg(FVector2D(Origin.X - shift, Origin.Y + shift), FVector2D(5, 5), Hlegs);
	GenerateLeg(FVector2D(Origin.X + shift, Origin.Y - shift), FVector2D(5, 5), Hlegs);
	GenerateLeg(FVector2D(Origin.X + shift, Origin.Y + shift), FVector2D(5, 5), Hlegs);

	// seat (Seat)
	GenerateSeat(FVector(Origin.X, Origin.Y, Hlegs), FVector(Wseat, Lseat, Hseat));

	// fixed W and L (Back)
	GenerateBack(FVector2D(Origin.X, Origin.Y+(17*dir)), FVector2D(40, 5), Hlegs, Hback);
}