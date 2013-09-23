//
//  ParticleSystem.h
//  NOC_4_08_ParticleSystemForcesRepeller
//
//  Created by Armin H. on 9/15/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "Particle.h"
//#include "Repeller.h"

class ParticleSystem {
    
    ci::Vec2f mOrigin; // origin location of particle system
    
public:
    ParticleSystem( ci::Vec2f );
    
    std::vector<Particle *> mParticles; // vector for collecting Particles
    ci::gl::Texture mTexture; // texture for a particle
    
    void addParticle();
    void applyForce( ci::Vec2f );
    void update();
    void draw();
};