#include "Chair.h"


int main(void) {
    Chair C( FVector{ 0, 0, 0 }, ChairData::Leg{ 5, 5, 100 }, ChairData::Seat{ 30, 40, 5 }, ChairData::Back{ 30, 5, 180}, 0.0 );
    C.rotate(-45);
    C.generate();
}


