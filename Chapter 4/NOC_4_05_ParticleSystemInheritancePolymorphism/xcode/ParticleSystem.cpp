//
//  ParticleSystem.cpp
//  NOC_4_05_ParticleSystemInheritancePolymorphism
//
//  Created by Armin H. on 9/15/13.
//
//

#include "ParticleSystem.h"

using namespace ci;

ParticleSystem::ParticleSystem( ci::Vec2f origin ) {
    mOrigin = origin;
//    addParticle();
    
}

void ParticleSystem::addParticle() {
    float r = randFloat();
//    mParticles.push_back( new Confetti (mOrigin) );
    
    if (r < 0.5) {
        mParticles.push_back( new Particle( mOrigin ) );
    } else {
        mParticles.push_back( new Confetti (mOrigin) );
    }
    
}


// A function to apply a force to all Particles
void ParticleSystem::applyForce(ci::Vec2f force) {
    for (auto p : mParticles) {
        p->applyForce( force );
    }
}


void ParticleSystem::update() {
    addParticle();
    for (int i = 0; i < mParticles.size(); i++) {
        Particle * p = mParticles.at( i );
        p->update();
        if ( p->isDead() ) {
            mParticles.erase( mParticles.begin() + i );
        }       
    }
}

void ParticleSystem::draw() {
    
    for (auto p : mParticles ) {
        p->draw();
    }
}