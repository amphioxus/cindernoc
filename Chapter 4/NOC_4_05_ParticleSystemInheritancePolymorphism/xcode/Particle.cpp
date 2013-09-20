//
//  Particle.cpp
//  NOC_4_05_ParticleSystemInheritancePolymorphism
//
//  Created by Armin H. on 9/15/13.
//
//

#include "Particle.h"


Particle::Particle( ci::Vec2f location) {
    // initialize new particle:
    mAcceleration = ci::Vec2f (0.0, 0.05);
    mVelocity = ci::Vec2f ( ci::randFloat(-1, 1), ci::randFloat(-1, 1) );
    mLocation = location;
    mLifeSpan = 255.;
}


void Particle::applyForce( ci::Vec2f force ) {
    mAcceleration += (force / mMass);
}

bool Particle::isDead() {
    
    if (mLifeSpan < 0.0)
        return TRUE;
    else
        return FALSE;
}

void Particle::run() {
    update();
    draw();
}

void Particle::update(){
    mVelocity += mAcceleration;
    mLocation += mVelocity;
    
    mAcceleration *= 0.0; // clear acceleration for next round
    mLifeSpan -= 2.0;
}


void Particle::draw() {
    
    float alpha = ci::lmap<float>(mLifeSpan, 0, 255, 0, 1);
    ci::gl::enableAlphaBlending();
    ci::gl::color(.8, .4, .4, alpha);
    ci::gl::drawSolidCircle( mLocation , 2.0);
    ci::gl::disableAlphaBlending();
}

