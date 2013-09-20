//
//  Mover.cpp
//
//  Created by Armin H. on 8/27/13.
//
//

#include "Mover.h"

// namespaces
using namespace ci;


Mover::Mover( ) {
	mMass =  1.0f;
    mLocation = Vec2f( randFloat(app::getWindowWidth()), randFloat(app::getWindowHeight()) );
	mVelocity = Vec2f::zero();
    mAcceleration = Vec2f::zero();
}

Mover::Mover(float m, float x, float y) {
    mMass = m;
    mLocation = Vec2f(x, y);
}


void Mover::update( ci::Vec2f mousepos ) {
    // first, save location for history trail:
    mLocationHistory.push_back( mLocation );
    if (mLocationHistory.size() > 100) {
        mLocationHistory.pop_front();
    }
    ci::Vec2f dir = mousepos - mLocation;
    dir.safeNormalize();
    mAcceleration = dir;
    mVelocity += mAcceleration;
    mVelocity.limit( topspeed );
    mLocation += mVelocity;
    
    
    mAcceleration *= 0;
    
}


void Mover::draw( ) {
	Rectf rect = Rectf( -30, -10, 30, 10 );
    float heading = toDegrees( atan2f(mVelocity.y, mVelocity.x) );
    
    gl::enableAlphaBlending();
    gl::color(0.68, 0.68, 0.68, 0.4);
    
    gl::pushMatrices();
    
    gl::translate(mLocation);
    gl::rotate(heading);
    
    gl::drawSolidRect(rect);
    
    gl::color(0, 0, 0, 1.);
    gl::lineWidth(2.0);
    gl::drawStrokedRect(rect);
    
    gl::popMatrices();
    
    
    gl::disableAlphaBlending();
}

void Mover::draw_history() {
    gl::enableAlphaBlending();
    ci::gl::color( ci::ColorA(.8f, .6f, .6f, 0.6f) );
    
    for (ci::Vec2f dot : mLocationHistory) {
        gl::drawSolidCircle(dot, 3.0);
    }
    gl::disableAlphaBlending();
}


void Mover::applyForce(Vec2f force) {
    Vec2f f = force / mMass;
    mAcceleration += f;
}

void Mover::checkEdges() {
    
    if (mLocation.x > app::getWindowWidth() ) {
        mLocation.x = 0;
    }
    else if (mLocation.x < 0) {
        mLocation.x = app::getWindowWidth();
    }
    
    if (mLocation.y > app::getWindowHeight() ) {
        mLocation.y = 0;
    }
    else if (mLocation.y < 0) {
        mLocation.y = app::getWindowHeight();
    }
}



Vec2f Mover::attract(MoverRef m) {
    float G = 0.4;
    Vec2f force = mLocation - m->mLocation;
    float distance = force.length();
    distance = math<float>::clamp(distance, 5.0, 25.0);
    force.safeNormalize();
    
    float strength = (G * mMass * m->mMass) / (distance * distance);
    force *= strength;
    return force;
}
