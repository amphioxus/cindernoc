//
//  Vehicle.cpp
//  NOC_6_01_Seek
//
//  Created by Armin H. on 10/3/13.
//
//

#include "Vehicle.h"


Vehicle::Vehicle( ci::Vec2f location ) {
    mLocation = location;
    
    mVelocity = ci::Vec2f(0, -2.);
    mAcceleration = ci::Vec2f(0.,0.);
    mR = 6.;
    maxForce = .1;
    maxSpeed = 5.;
}


void Vehicle::update() {
    // Update velocity
    mVelocity += mAcceleration;
    // Limit speed
    mVelocity.limit( maxSpeed );
    mLocation += mVelocity;
    // Reset accelerationelertion to 0 each cycle
    mAcceleration *= 0;
    
    // calculate heading:
    mTheta = atan2f(mVelocity.y, mVelocity.x);
}


void Vehicle::seek( ci::Vec2f target ) {
    // A method that calculates a steering force towards a target
    // STEER = DESIRED MINUS VELOCITY
    ci::Vec2f desired = target - mLocation;
    // Normalize desired and scale to maximum speed
    desired.safeNormalize();
    desired *= maxSpeed;
    // Steering = Desired minus velocity
    ci::Vec2f steer = desired - mVelocity;
    steer.limit( maxForce );
    applyForce( steer );
}


void Vehicle::applyForce( ci::Vec2f force ) {
    mAcceleration += (force / mMass);
}


void Vehicle::draw() {
    ci::gl::enableAlphaBlending();
    ci::gl::pushMatrices();
    
    ci::gl::translate( mLocation );
    ci::gl::rotate( ci::toDegrees(mTheta)+90 );
    ci::gl::color(.4, .4, .4);
    ci::gl::begin( GL_POLYGON );
    ci::gl::vertex( ci::Vec2f(0, -mR*2) );
    ci::gl::vertex( ci::Vec2f(-mR, mR*2) );
    ci::gl::vertex( ci::Vec2f(mR, mR*2) );
    ci::gl::end();
    
    ci::gl::popMatrices();
    ci::gl::disableAlphaBlending();
}

