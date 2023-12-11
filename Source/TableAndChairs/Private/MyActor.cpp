// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	m_Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = m_Mesh;
	m_Mesh->bUseAsyncCooking = true;
}

// This is called when actor is spawned (at runtime or when you drop it into the world in editor)
void AMyActor::PostActorCreated()
{
	Super::PostActorCreated();
	GenerateMesh();
}

// This is called when actor is already in level and map is opened
void AMyActor::PostLoad()
{
	Super::PostLoad();
	GenerateMesh();

}

FVector AMyActor::ComputeFaceNormal(const FVector& A, const FVector& B, const FVector& C)
{
	FVector Edge1 = B - A;
	FVector Edge2 = C - A;
	FVector Normal = FVector::CrossProduct(Edge1, Edge2).GetSafeNormal();
	return Normal;
}


void AMyActor::ComputeVertexNormals()
{
	// Initialize normals
	Normals.Init(FVector::ZeroVector, Vertices.Num());

	// Calculate face normals and accumulate them for each vertex
	for (int32 i = 0; i < Triangles.Num(); i += 3)
	{
		int32 VertexIndexA = Triangles[i];
		int32 VertexIndexB = Triangles[i + 1];
		int32 VertexIndexC = Triangles[i + 2];

		FVector FaceNormal = ComputeFaceNormal(Vertices[VertexIndexA], Vertices[VertexIndexB], Vertices[VertexIndexC]);

		// Accumulate normals for each vertex of the face
		Normals[VertexIndexA] += FaceNormal;
		Normals[VertexIndexB] += FaceNormal;
		Normals[VertexIndexC] += FaceNormal;
	}

	// Normalize vertex normals
	for (FVector& Normal : Normals)
	{
		Normal.Normalize();
	}
}


void AMyActor::GetTangentFromNormal()
{
	FVector tangentVec, bitangentVec;
	FVector c1, c2;
	TArray<FVector> AccTangents;
	AccTangents.Init(FVector::ZeroVector, Normals.Num());

	for (int32 i = 0; i < Normals.Num(); i += 3) {
		c1 = FVector::CrossProduct(Normals[i], FVector(0.0f, 0.0f, 1.0f));
		c2 = FVector::CrossProduct(Normals[i], FVector(0.0f, 1.0f, 0.0f));

		if (c1.Size() > c2.Size())
		{
			tangentVec = c1;
		}
		else
		{
			tangentVec = c2;
		}

		tangentVec = tangentVec.GetSafeNormal();
		bitangentVec = FVector::CrossProduct(Normals[i], tangentVec);
		AccTangents.Add(bitangentVec);
	}

	for (FVector& tangent : AccTangents) {
		tangent.Normalize();
		Tangents.Add(FProcMeshTangent(tangent, false));
	}
}

void AMyActor::CalculateUVs()
{
	UVs.Empty();

	for (const FVector& Vertex : Vertices)
	{
		// Assuming a simple mapping where U and V are based on X and Y coordinates
		float U = FMath::Fractional(1.0);
		float V = FMath::Fractional(1.0);

		UVs.Add(FVector2D(U, V));
	}
}

void AMyActor::GenerateMesh()
{
	Vertices.Reset();
	Triangles.Reset();
	Normals.Reset();
	UVs.Reset();
	Colors.Reset();
	Tangents.Reset();

	FVector vertexes[8];
	//FProcMeshTangent tangent;

	vertexes[0] = FVector(x, -y, z);
	vertexes[1] = FVector(x, -y, -z);
	vertexes[2] = FVector(x, y, -z);
	vertexes[3] = FVector(x, y, z);

	vertexes[4] = FVector(-x, -y, z);
	vertexes[5] = FVector(-x, -y, -z);
	vertexes[6] = FVector(-x, y, -z);
	vertexes[7] = FVector(-x, y, z);

	Vertices.Add(vertexes[0]);	// 1
	Vertices.Add(vertexes[1]);	// 0
	Vertices.Add(vertexes[2]);	// 2
	Vertices.Add(vertexes[3]);	// 3
				 
	Vertices.Add(vertexes[4]);	// 4
	Vertices.Add(vertexes[5]);	// 5
	Vertices.Add(vertexes[6]);	// 6
	Vertices.Add(vertexes[7]);	// 7


	//front
	//tangent = FProcMeshTangent(0.f, 1.f, 0.f);
	AddQuad(TArray<double>{ 3.0, 2.0, 1.0 }, TArray<double>{ 1.0, 0.0, 3.0 });
	AddQuad(TArray<double>{ 7.0, 4.0, 5.0 }, TArray<double>{ 5.0, 6.0, 7.0 });
	AddQuad(TArray<double>{ 7.0, 6.0, 2.0 }, TArray<double>{ 2.0, 3.0, 7.0 });
	AddQuad(TArray<double>{ 4.0, 0.0, 1.0 }, TArray<double>{ 1.0, 5.0, 4.0 });
	AddQuad(TArray<double>{ 6.0, 5.0, 1.0 }, TArray<double>{ 1.0, 2.0, 6.0 });
	AddQuad(TArray<double>{ 7.0, 3.0, 0.0 }, TArray<double>{ 0.0, 4.0, 7.0 });

	ComputeVertexNormals();
	GetTangentFromNormal();
	CalculateUVs();

	Colors.Init(FLinearColor::Green, 8);
	m_Mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);

	// Enable collision data
	m_Mesh->ContainsPhysicsTriMeshData(true);
}

void AMyActor::AddQuad(TArray<double> Idx1, TArray<double> Idx2)
{
	Triangles.Add(Idx1[0]);
	Triangles.Add(Idx1[1]);
	Triangles.Add(Idx1[2]);

	Triangles.Add(Idx2[0]);
	Triangles.Add(Idx2[1]);
	Triangles.Add(Idx2[2]);
}
