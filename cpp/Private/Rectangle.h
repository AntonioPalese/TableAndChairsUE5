
namespace utils{
    FVector rotate(FVector P, double angle);
}


class Rectangle{
public:
    Rectangle(FVector origin, FVector size, double angle, FString mode, TArray<FVector>* vertexes,  TArray<FVector>* triangles, int32& counter);

    Rectangle* rotate(FVector2D center, double angle);
    Rectangle* rotate(double angle);
    // void draw();
    // void _mesh();
private:
    FVector m_Origin;
    FVector m_Size;
    double m_Angle;

    TArray<FVector>* m_Vertexes;
    TArray<Rectangle*> m_Children;
    TArray<int32>* m_Triangles;
    TArray<int32> m_Indexes;
}