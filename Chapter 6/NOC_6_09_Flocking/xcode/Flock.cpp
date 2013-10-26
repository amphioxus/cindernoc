//
//  Flock.cpp
//  NOC_6_09_Flocking
//
//  Created by Armin H. on 10/23/13.
//
//

#include "Flock.h"


Flock::Flock() {
    
}

void Flock::addBoid( Boid * boid ) {
    mBoids.push_back( boid );
}


void Flock::update() {
    for (auto b : mBoids ) {
        b->applyBehaviors( mBoids );
    }
}

void Flock::draw() {
    for (auto b : mBoids  ) {
        b->draw();
    }
}