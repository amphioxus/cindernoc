//
//  Repeller.h
//  NOC_4_07_ParticleSystemForcesRepeller
//
//  Created by Armin H. on 9/17/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/CinderMath.h"
#include "Particle.h"

class Repeller {
  
public:
    Repeller( ci::Vec2f );
    
    float mG = 100;  // Gravitational Constant
    ci::Vec2f mLocation;
    ci::Vec2f mDirection;
    
    ci::Vec2f repel( Particle * );
    void draw();

};