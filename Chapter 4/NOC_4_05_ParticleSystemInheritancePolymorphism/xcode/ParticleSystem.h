//
//  ParticleSystem.h
//  NOC_4_05_ParticleSystemInheritancePolymorphism
//
//  Created by Armin H. on 9/15/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "Particle.h"
#include "Confetti.h"

class ParticleSystem {
    
    ci::Vec2f mOrigin; // origin location of particle system
    
public:
    ParticleSystem( ci::Vec2f );
    
    std::vector<Particle *> mParticles; // vector holding particles (and confetti child objects)
    
    void addParticle();
    void applyForce( ci::Vec2f );
    void update();
    void draw();
};