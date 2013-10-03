//
//  CollisionListener.cpp
//  NOC_5_9_CollisionListening
//
//  Created by Armin H. on 10/2/13.
//
//

#include "CollisionListener.h"


void CollisionListener::BeginContact(b2Contact* contact) {
    
    void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    // if both have user data, they are both particles:
    if ( bodyUserDataA && bodyUserDataB) {
        static_cast<Particle *>( bodyUserDataA )->startContact();
        static_cast<Particle *>( bodyUserDataB )->startContact();
    }
}


void CollisionListener::EndContact(b2Contact* contact) {
    // this info is not used in this example, but it's here to show a variant of the code above that would also detect collisions with the wall
    //check if fixture A was a particle (i.e. has user data)
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Particle *>( bodyUserData )->endContact();
    
    //check if fixture B was a particle
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Particle*>( bodyUserData )->endContact();
}