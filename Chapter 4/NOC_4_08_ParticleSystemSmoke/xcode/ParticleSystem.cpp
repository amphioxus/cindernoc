//
//  ParticleSystem.cpp
//  NOC_4_07_ParticleSystemForcesRepeller
//
//  Created by Armin H. on 9/15/13.
//
//

#include "ParticleSystem.h"

using namespace ci;

ParticleSystem::ParticleSystem( ci::Vec2f origin ) {
    mOrigin = origin;
    mTexture = ci::loadImage( ci::app::loadResource("texture.png")  );
}

void ParticleSystem::addParticle() {
    mParticles.push_back( new Particle( mOrigin, mTexture ) );
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