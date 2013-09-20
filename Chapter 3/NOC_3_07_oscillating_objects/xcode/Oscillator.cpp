//
//  Oscillator.cpp
//  NOC_3_07_oscillating_objects
//
//  Created by Armin H. on 9/12/13.
//
//


#include "Oscillator.h"

// namespaces
using namespace ci;


// standard constructor:
Oscillator::Oscillator() {

    mVelocity.x = ci::randFloat(-0.05, 0.05);
    mVelocity.y = ci::randFloat(-0.05, 0.05);
    mAmplitude.x = ci::randFloat( 40.0, (float) ci::app::getWindowWidth() / 2 );
    mAmplitude.y = ci::randFloat( 40.0, (float) ci::app::getWindowHeight() / 2 );

}


void Oscillator::oscillate() {
    mAngle += mVelocity;
}



void Oscillator::draw() {
    
    ci::Vec2f center ( sin( mAngle.x ) * mAmplitude.x,
                       sin( mAngle.y ) * mAmplitude.y    );
    
    gl::enableAlphaBlending();
    gl::pushMatrices();
    
    int ww = ci::app::getWindowWidth();
    int wh = ci::app::getWindowHeight();
    gl::translate( ci::Vec2f ( ww/2, wh/2));
    gl::color(.8f, .6f, .6f, 0.6f);
    gl::drawLine( ci::Vec2f (0,0), center);
    gl::drawSolidCircle(center, 12);
    
    gl::popMatrices();
    gl::disableAlphaBlending();

}