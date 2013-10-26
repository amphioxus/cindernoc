//
//  Flock.h
//  NOC_6_09_Flocking
//
//  Created by Armin H. on 10/23/13.
//
//


#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "Boid.h"

class Flock {
    
public:
    Flock();
    
    std::vector< Boid *> mBoids; // container for our flock
    void addBoid( Boid * );
    void update();
    void draw();
};
