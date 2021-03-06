//
//  Particle.h
//  NOC_4_06_ParticleSystemForces
//
//  Created by Armin H. on 9/15/13.
//
//

#pragma once
#include <iostream>
#include "cinder/Rand.h"

class Particle {
    
    float mLifeSpan;
    float mMass = 1;
    ci::Vec2f mLocation;
    ci::Vec2f mVelocity;
    ci::Vec2f mAcceleration;
    
public:
    Particle( ci::Vec2f );
    
    void applyForce( ci::Vec2f );
    bool isDead();
    void run();     // convenience method to update and draw
    void update();  // Method to update location
    void draw();
    
    
};