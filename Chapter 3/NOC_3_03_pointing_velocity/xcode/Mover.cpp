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
    mLocation.x = ci::app::getWindowWidth()/2;
    mLocation.y = ci::app::getWindowHeight()/2;
    mVelocity.x = 0.;  mVelocity.y = 0.;
    mAcceleration.x = 0;  mAcceleration.y = 0;
//    mMass = ci::Rand::randFloat(0.5, 2.);
    mColor = ci::ColorA(1.0f, 0.5f, 0.25f, 0.3f);
}


Mover::Mover(float x, float y) {
    
    mLocation.x = x; mLocation.y =y;
    mVelocity.x = 0.;  mVelocity.y = 0.;
    mAcceleration.x = 0;  mAcceleration.y = 0;
    
    mColor = ci::ColorA(1.0f, 0.5f, 0.25f, 0.3f);
}

void Mover::update(  ci::Vec2f mousepos  ) {
    mHistory.push_back(mLocation); // remember position
    if (mHistory.size() > 200){
        mHistory.pop_front();
    }
    
    ci::Vec2f dir = mousepos - mLocation;
    dir.safeNormalize();
    mAcceleration = 0.5 * dir;
    mVelocity += mAcceleration;
    mVelocity.limit( mTopspeed );
    mLocation += mVelocity;
    // calculate heading:
    mTheta = atan2f(mVelocity.y, mVelocity.x);
}


void Mover::checkEdges() {
    
    if (mLocation.x > ci::app::getWindowWidth() ) {
        mLocation.x = 0;
    }
    else if (mLocation.x < 0) {
        mLocation.x = ci::app::getWindowWidth();
    }
    
    if (mLocation.y > ci::app::getWindowHeight() ) {
        mLocation.y = 0;
    } else if (mLocation.y < 0) {
        mLocation.y = ci::app::getWindowHeight();
    }
}


void Mover::draw() {
    
    // Turn on additive blending
    ci::gl::enableAlphaBlending();
    ci::gl::pushMatrices();
    ci::gl::translate( mLocation );
    ci::gl::rotate( ci::toDegrees( mTheta ) );
    ci::gl::color( mColor );
    ci::gl::drawSolidRect( mRect );
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