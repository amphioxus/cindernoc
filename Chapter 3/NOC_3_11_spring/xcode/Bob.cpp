//
//  Bob.cpp
//  NOC_3_11_spring
//
//  Created by Armin H. on 9/14/13.
//
//

#include "Bob.h"
using namespace ci;

Bob::Bob( ci::Vec2f location ) {
    
    mLocation = location;
    
}

void Bob::clicked(ci::Vec2f mousepos) {
    ci::Vec2f dvec = mLocation - mousepos;
    float dist = dvec.length();
    if (dist < mMass) {
        mDragging = TRUE;
        mLocation = mousepos;
        mAcceleration *= 0.;
    }
}

void Bob::drag(ci::Vec2f mousepos ) {
    if (mDragging) {
        mLocation = mousepos;
    }
}

void Bob::stopDragging() {
    mDragging = FALSE;
}

void Bob::update() {
    // Standard Euler integration
    mVelocity += mAcceleration;
    mVelocity *= mDamping;
    mLocation += mVelocity;
    
    // clear acceleration for next round
    mAcceleration *= 0.;
}


void Bob::applyForce( ci::Vec2f force ) {
    // Newton's law: F = M * A
    mAcceleration += force / mMass;
}


void Bob::draw() {
    
    gl::enableAdditiveBlending();
    if (mDragging)
        ci::gl::color(0.f, .6f, .4f, 1.f);
    else
        ci::gl::color(0.f, .6f, .4f, 0.6f);
    
    gl::drawSolidCircle( mLocation, mMass );
    
    gl::disableAlphaBlending();
}