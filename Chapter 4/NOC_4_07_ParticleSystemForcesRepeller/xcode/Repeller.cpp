//
//  Repeller.cpp
//  NOC_4_07_ParticleSystemForcesRepeller
//
//  Created by Armin H. on 9/17/13.
//
//

#include "Repeller.h"


Repeller::Repeller( ci::Vec2f location ) {
    mLocation = location;
    
}

ci::Vec2f  Repeller::repel( Particle * p ) {
    
    mDirection = mLocation - p->mLocation;      // Calculate direction of force
    float dist = mDirection.length();           // Distance between objects
    mDirection.safeNormalize();                 // Normalize vector (distance doesn't matter here, we just want this vector for direction)
    
    dist = ci::math<float>::clamp(dist, 5., 100.);
    
    return mDirection * ( (-1 * mG) / (dist * dist) );
    
}

void Repeller::draw() {
    
    ci::gl::enableAlphaBlending();
    ci::gl::color(1.0, 0.45, 0., 0.8);
    ci::gl::drawSolidCircle( mLocation , 8.0);
    ci::gl::disableAlphaBlending();
}