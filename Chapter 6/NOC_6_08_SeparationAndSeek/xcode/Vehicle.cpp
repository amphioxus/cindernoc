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
    mVelocity = ci::Vec2f(0., 0.);
    mAcceleration = ci::Vec2f(0.,0.);
    mR = 12.;
    mMaxForce = .2;
    mMaxSpeed = 3.;
}


void Vehicle::update() {

    // Update velocity
    mVelocity += mAcceleration;
    // Limit speed
    mVelocity.limit( mMaxSpeed );
    mLocation += mVelocity;
    // Reset accelerationelertion to 0 each cycle
    mAcceleration *= 0;
}

void Vehicle::applyBehaviors( std::vector< Vehicle * > vehicles, ci::Vec2f mousepos ) {
    //
    applyForce( separate( vehicles )*2 );
    applyForce( seek( mousepos ) );
}

ci::Vec2f Vehicle::seek( ci::Vec2f target ) {
    // A method that calculates a steering force towards a target
    // STEER = DESIRED MINUS VELOCITY
    ci::Vec2f desired = target - mLocation;
    // Normalize desired and scale to maximum speed
    desired.safeNormalize();
    desired *= mMaxSpeed;
    // Steering = Desired minus velocity
    ci::Vec2f steer = desired - mVelocity;
    steer.limit( mMaxForce );
    return steer;
}


ci::Vec2f Vehicle::separate( std::vector< Vehicle * > vehiclelist ) {
    float desiredSeparation = 2 * mR;
    int count = 0;
    ci::Vec2f vectorSum = ci::Vec2f (0,0);
    // For every boid in the system, check if it's too close
    for (auto other : vehiclelist) {
        float d = (mLocation - other->mLocation).length();
        // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
        if (d > 0 && d < desiredSeparation ) {
            // Calculate vector pointing away from neighbor
            ci::Vec2f diff = mLocation - other->mLocation;
            
            vectorSum += diff.normalized() / d; // Weight by distance
            count++;
        }
    }
    
    // Average -- divide by how many
    if (count > 0 ) {
        vectorSum = vectorSum / count;
        // Our desired vector is the average scaled to maximum speed
         // Implement Reynolds: Steering = Desired - Velocity
        ci::Vec2f steer =  ( vectorSum.normalized() * mMaxSpeed ) - mVelocity;
        steer.limit( mMaxForce );
        return steer;
    } else
        return ci::Vec2f (0,0);
}


void Vehicle::checkBorders() {
    if (mLocation.x < -mR) { mLocation.x = ci::app::getWindowWidth()+mR; }
    if (mLocation.x > ci::app::getWindowWidth()+mR) { mLocation.x = -mR; }
    if (mLocation.y < -mR) { mLocation.y = ci::app::getWindowHeight() + mR; }
    if (mLocation.y > ci::app::getWindowWidth() + mR ) { mLocation.y = -mR; }
}


void Vehicle::applyForce( ci::Vec2f force ) {
    mAcceleration += (force / mMass);
}


void Vehicle::draw() {
//    ci::gl::enableAlphaBlending();
    
    ci::gl::color(.6, .6, .6);
    ci::gl::drawSolidCircle( mLocation, mR/2 );
    ci::gl::color(0, 0, 0);
    ci::gl::drawStrokedCircle( mLocation, mR/2 );
//    ci::gl::disableAlphaBlending();
}




