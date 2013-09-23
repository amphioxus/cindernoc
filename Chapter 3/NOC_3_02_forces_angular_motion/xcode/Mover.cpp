//
//  Mover.cpp
//
//  Created by Armin H. on 8/27/13.
//
//

#include "Mover.h"

// Default constructor
Mover::Mover() {
    
    ci::Rand::randomize();
    mLocation.x = ci::Rand::randFloat( ci::app::getWindowWidth() );
    mLocation.y = ci::Rand::randFloat( ci::app::getWindowHeight() );
    mVelocity.x = 0.;  mVelocity.y = 0.;
    mAcceleration.x = 0;  mAcceleration.y = 0;
    mMass = ci::Rand::randFloat(0.5, 2.);
    mColor = ci::ColorA(1.0f, 0.5f, 0.25f, 0.3f);
}


Mover::Mover(float m, float x, float y) {
    
    mLocation.x = x; mLocation.y =y;
    mVelocity.x = 0.;  mVelocity.y = 0.;
    mAcceleration.x = 0;  mAcceleration.y = 0;
    mMass = m;
    
    mColor = ci::ColorA(1.0f, 0.5f, 0.25f, 0.3f);
}

void Mover::update() {
    mHistory.push_back(mLocation); // remember position
    if (mHistory.size() > 200){
//        mHistory.pop_back();
        mHistory.pop_front();
    }
    
    mVelocity += mAcceleration;
    mLocation += mVelocity;
    
    mAngleAcceleration = mAcceleration.x / 20.0;
    mAngleVelocity += mAngleAcceleration;
    mAngle += ci::math<float>::clamp(mAngleVelocity, -0.1, 0.1);
    
    mAcceleration *= 0; // set acceleration to zero after each cycle
}

ci::Vec2f Mover::attract(Mover * m) {
    
    ci::Vec2f force = m->mLocation - mLocation;     // Calculate direction of force
    float distance = force.length();             // Distance between objects
    // Limiting the distance to eliminate "extreme" results for very close or very far objects:
    if ( distance < 5.0 )
        distance = 5.0;
    else if (distance > 25.0)
        distance = 25.0;
    
    float strength = (mG * mMass * m->mMass) / (distance * distance); // Calculate gravitional force magnitude
    
    return force.safeNormalized() * strength;   // Get force vector --> magnitude * direction
}


void Mover::applyForce(ci::Vec2f force) {
    force /= mMass;
    mAcceleration += force;
}


void Mover::checkEdges() {
    
    if (mLocation.x > ci::app::getWindowWidth() ) {
        mLocation.x = ci::app::getWindowWidth();
        mVelocity.x *= -1;
    }
    else if (mLocation.x < 0) {
        mLocation.x = 0;
        mVelocity.x *= -1;
    }
    
    if (mLocation.y > ci::app::getWindowHeight() ) {
        mLocation.y = ci::app::getWindowHeight();
        mVelocity.y *= -1;
    }
}


void Mover::draw() {
    
    ci::Rectf rect = ci::Rectf(-8*mMass, 8*mMass, 8*mMass, -8*mMass);
    
    // Turn on additive blending
    ci::gl::enableAlphaBlending();
    ci::gl::pushMatrices();
    ci::gl::translate(mLocation);
    ci::gl::rotate(ci::toDegrees(mAngle));
    ci::gl::color( mColor );
    ci::gl::drawSolidRect( rect );
    ci::gl::popMatrices();
    ci::gl::disableAlphaBlending();
}


void Mover::draw_history() {
    // Turn on additive blending
    ci::gl::enableAlphaBlending();
    ci::gl::color( ci::ColorA(.8f, .6f, .6f, 0.6f) );
    // iterate through history of each mover
    
    for (auto it : mHistory) {
        ci::gl::drawSolidCircle( ci::Vec2f (it.x, it.y), 1.5);
    }

    ci::gl::disableAlphaBlending();
}