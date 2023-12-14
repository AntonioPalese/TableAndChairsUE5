class Cuboid{
public:
    Cuboid(FVector origin, FVector size, double angle);
    void generate();
    void rotate(FVector2D center, double angle );
    void rotate(double angle );
private:
    FVector m_Origin;
    FVector m_Size;
    double m_Angle;

    TArray<Rectangle*> m_Children;
    TArray<FVector> m_Vertexes;
    TArray<FVector> m_Triangles;
    int32 m_Counter;
} 