//
//  Boid.cpp
//  NOC_6_09_Flocking
//
//  Created by Armin H. on 10/23/13.
//
//

#include "Boid.h"



Boid::Boid( ci::Vec2f location) {

    mLocation = location;
    mVelocity = ci::Vec2f( ci::randFloat(-1.f, 1.f), ci::randFloat(-1.f, 1.f));
    mAcceleration = ci::Vec2f(0.,0.);
    
    mR = 3.0;
    mMaxForce = 0.05;
    mMaxSpeed = 3.0;
}



// We accumulate a new acceleration each time based on three rules
void Boid::flock( std::vector< Boid * > boidList ) {
    ci::Vec2f sepF = separate( boidList );
    ci::Vec2f alF = align( boidList );
    ci::Vec2f coF = cohere( boidList );
    // Arbitrarily weight these forces
    sepF *= 1.5;
//    alF *= 1;
//    coF *= 1.; 
    // Add the force vectors to acceleration
    applyForce( sepF );
    applyForce( alF );
    applyForce( coF );
}


void Boid::applyBehaviors( std::vector< Boid * > boidList ) {
    flock( boidList );
    update();
    checkBorders();
}


void Boid::update() {
    // Update velocity
    mVelocity += mAcceleration;
    // Limit speed
    mVelocity.limit( mMaxSpeed );
    mLocation += mVelocity;
    // Reset accelerationelertion to 0 each cycle
    mAcceleration *= 0;
    // calculate heading:
    mTheta = atan2f(mVelocity.y, mVelocity.x);
}



// A method that calculates and applies a steering force towards a target
// STEER = DESIRED MINUS VELOCITY
ci::Vec2f Boid::seek( ci::Vec2f target ) {
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


// Separation
// Method checks for nearby boids and steers away
ci::Vec2f Boid::separate( std::vector<Boid *> boidList ) {
    float desiredSeparation = 5 * mR;
    desiredSeparation = desiredSeparation * desiredSeparation; // square it to use lengthsquared later
    int count = 0;
    ci::Vec2f vectorSum = ci::Vec2f (0,0);
    // For every boid in the system, check if it's too close
    for (auto other : boidList) {
        float d = (mLocation - other->mLocation).lengthSquared();
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


// Alignment
// For every nearby boid in the system, calculate the average velocity
ci::Vec2f Boid::align( std::vector< Boid * > boidList ) {
    float neighborDist = 50;
    neighborDist = neighborDist * neighborDist; // square it to use lengthsquared later
    ci::Vec2f vectorSum = ci::Vec2f (0,0);
    int count = 0;
    
    for (auto other : boidList ) {
        float d = ( mLocation - other->mLocation ).lengthSquared();
        
        if (d > 0 && d < neighborDist ) {
            vectorSum += other->mVelocity;
            
            count++;
        }
        
    }
    
    if ( count > 0 ) {
        vectorSum = vectorSum / (float)count;
        vectorSum.normalize();
        vectorSum *= mMaxSpeed;
        ci::Vec2f steer = vectorSum - mVelocity;
        steer.limit( mMaxForce );
        return steer;
    } else
        return ci::Vec2f(0,0);
}


// Cohesion
// For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
ci::Vec2f Boid::cohere( std::vector<Boid *> boidList ) {
    float neighborDist = 50;
    neighborDist = neighborDist * neighborDist; // square it to use lengthsquared later
    ci::Vec2f vectorSum = ci::Vec2f (0,0);
    int count = 0;
    
    for (auto other : boidList ) {
        float d = ( mLocation - other->mLocation ).lengthSquared();
        if (d > 0 && d < neighborDist ) {
            vectorSum += other->mLocation;
            count++;
        }
    }
    
    if ( count > 0 ) {
        vectorSum /= count;
        return seek( vectorSum );
    } else {
        return ci::Vec2f (0,0);
    }
}



void Boid::applyForce( ci::Vec2f force ) {
    mAcceleration += (force / mMass);
}


// Wraparound
void Boid::checkBorders() {
    if (mLocation.x < -mR) { mLocation.x = ci::app::getWindowWidth()+mR; }
    if (mLocation.x > ci::app::getWindowWidth()+mR) { mLocation.x = -mR; }
    if (mLocation.y < -mR) { mLocation.y = ci::app::getWindowHeight() + mR; }
    if (mLocation.y > ci::app::getWindowHeight() + mR ) { mLocation.y = -mR; }
}


void Boid::draw() {
    
    ci::gl::enableAlphaBlending();
    ci::gl::pushMatrices();
    
    ci::gl::translate( mLocation );
    ci::gl::rotate( ci::toDegrees(mTheta)+90 );
    ci::gl::color(.6, .6, .6);
    ci::gl::begin( GL_POLYGON );
    ci::gl::vertex( ci::Vec2f(0, -mR*2) );
    ci::gl::vertex( ci::Vec2f(-mR, mR*2) );
    ci::gl::vertex( ci::Vec2f(mR, mR*2) );
    ci::gl::end();
    ci::gl::color(0, 0, 0);
    ci::gl::lineWidth(1.0);
    ci::gl::begin( GL_LINE_LOOP );
    ci::gl::vertex( ci::Vec2f(0, -mR*2) );
    ci::gl::vertex( ci::Vec2f(-mR, mR*2) );
    ci::gl::vertex( ci::Vec2f(mR, mR*2) );
    ci::gl::end();
    ci::gl::popMatrices();
    ci::gl::disableAlphaBlending();
}