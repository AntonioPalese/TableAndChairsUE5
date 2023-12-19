#include "Cuboid.h"

Cuboid::Cuboid( FVector origin, FVector size, double angle, int nsections, UProceduralMeshComponent* mesh ) : m_Mesh(mesh), Nsections(nsections)
{
    m_Origin = origin;
    m_Size = size;
    m_Angle = angle;

    double dx = m_Size.X;
    double dy = m_Size.Y;
    double dz = m_Size.Z;

    // top
	for(int i = 0; i < 4; i++){
		m_Normals.Add(FVector(0.0, 0.0, 1.0));
		m_Tangents.Add(FProcMeshTangent(0.0, 1.0, 0.0));
	}
    m_Children.Add( new Rectangle(FVector(0.0, 0.0, 50.0), FVector(100.0, 100.0, 0.0), 0.0, "xy", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, true) );
   // bottom
	for (int i = 0; i < 4; i++) {
		m_Normals.Add(FVector(0.0, 0.0, -1.0));
		m_Tangents.Add(FProcMeshTangent(0.0, -1.0, 0.0));
	}
    m_Children.Add( new Rectangle( FVector(0.0, 0.0, -50.0), FVector(100.0, 100.0, 0.0), 0.0, "xy", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, false ) );
   // back
	for (int i = 0; i < 4; i++) {
		m_Normals.Add(FVector(1.0, 0.0, 0.0));
		m_Tangents.Add(FProcMeshTangent(0.0, 1.0, 0.0));
	}
    m_Children.Add( new Rectangle( FVector(50.0, 0.0, 0.0), FVector(0.0, 100.0, 100.0), 0.0, "yz", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, false ) );
    // front
	for (int i = 0; i < 4; i++) {
		m_Normals.Add(FVector(-1.0, 0.0, 0.0));
		m_Tangents.Add(FProcMeshTangent(0.0, -1.0, 0.0));
	}
    m_Children.Add( new Rectangle(FVector(-50.0, 0.0, 0.0), FVector(0.0, 100.0, 100.0), 0.0, "yz", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, true ) );
    // left
	for (int i = 0; i < 4; i++) {
		m_Normals.Add(FVector(0.0, 1.0, 0.0));
		m_Tangents.Add(FProcMeshTangent(0.0, 0.0, 1.0));
	}
    m_Children.Add( new Rectangle( FVector(0.0, 50.0, 0.0), FVector(100.0, 0.0, 100.0), 0.0, "xz", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, false ) );
    // right
	for (int i = 0; i < 4; i++) {
		m_Normals.Add(FVector(0.0, -1.0, 0.0));
		m_Tangents.Add(FProcMeshTangent(0.0, 0.0, -1.0));
	}
    m_Children.Add( new Rectangle( FVector(0.0, -50.0, 0.0), FVector(100.0, 0.0, 100.0), 0.0, "xz", m_Vertexes, m_Triangles, m_Normals, m_Tangents, m_UVs, m_Counter, true ) );
}

Cuboid::~Cuboid()
{
    for ( Rectangle* c : m_Children ) {
        delete c;
        c = nullptr;
    }
}

void Cuboid::generate()
{
    m_Mesh->SetMaterial(Nsections, m_Material);
	m_Mesh->CreateMeshSection_LinearColor(Nsections++, m_Vertexes, m_Triangles, m_Normals, m_UVs, Colors, m_Tangents, true);
}

void Cuboid::rotate( double angle )
{
    this->rotate( m_Origin, angle );
}

void Cuboid::rotate( FVector center, double angle )
{
    for ( auto c : m_Children ) {
        c->rotate( center, angle );
    }
}
