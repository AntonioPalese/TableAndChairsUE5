#include "Chair.h"
#include "Utils.h"

Chair::Chair( FVector origin, ChairData::Leg leg, ChairData::Seat seat, ChairData::Back back, double angle ) : m_Origin( origin )
{
    m_Components.push_back( new Cuboid( FVector( origin.X - seat.WSeat / 2, origin.Y - seat.LSeat / 2, origin.Z ), FVector( leg.WLegs, leg.LLegs, leg.HLegs ), angle ) );
    m_Components.push_back( new Cuboid( FVector( origin.X + seat.WSeat / 2, origin.Y + seat.LSeat / 2, origin.Z ), FVector( leg.WLegs, leg.LLegs, leg.HLegs ), angle ) );
    m_Components.push_back( new Cuboid( FVector( origin.X + seat.WSeat / 2, origin.Y - seat.LSeat / 2, origin.Z ), FVector( leg.WLegs, leg.LLegs, leg.HLegs ), angle ) );
    m_Components.push_back( new Cuboid( FVector( origin.X - seat.WSeat / 2, origin.Y + seat.LSeat / 2, origin.Z ), FVector( leg.WLegs, leg.LLegs, leg.HLegs ), angle ) );

    m_Components.push_back( new Cuboid( FVector( origin.X, origin.Y, origin.Z + leg.HLegs / 2 + seat.HSeat / 2 ), FVector( seat.WSeat + leg.WLegs, seat.LSeat + leg.WLegs, seat.HSeat ), angle ) );
    
    m_Components.push_back( new Cuboid( FVector( origin.X, origin.Y + seat.LSeat/2, origin.Z + leg.HLegs/2 + back.HBack/2 ), FVector( back.WBack, back.LBack, back.HBack ), angle ) );

}

Chair::~Chair()
{
    for ( Cuboid* c : m_Components ) {
        delete c;
        c = nullptr;
    }
}

void Chair::generate()
{
    for ( const auto component : m_Components ) {
        component->generate();
    }

    utilities::exec();
}

void Chair::rotate( FVector center, double angle )
{
    for ( const auto component : m_Components ) {
        component->rotate( center, angle );
    }
}

void Chair::rotate( double angle )
{
    rotate( m_Origin, angle );
}

