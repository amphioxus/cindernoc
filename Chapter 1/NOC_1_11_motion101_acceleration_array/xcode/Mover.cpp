//
//  Mover.cpp
//  NOC_1_9_motion101_acceleration
//
//  Created by Armin H. on 8/27/13.
//
//

#include "Mover.h"


Mover::Mover() {
    
 // Without a "Mover controller" class (or at least collecting movers in a std::list in the main app class) the getWindowWidth function can't be called because when the object is declared, no window exists yet. This leads to an exception.
    ci::Rand::randomize();
    location.x = ci::Rand::randFloat( 800. );
    location.y = ci::Rand::randFloat( 200.);
    velocity.x = 0.;
    velocity.y = 0.;
        
    topspeed = 8;
    
//    mColor = ci::ColorA(0.8, .4, .4, .5);
    mColor = ci::ColorA(1.0f, 0.5f, 0.25f, 0.3f);
}

void Mover::update(ci::Vec2f mousepos) {
    
    // Compute a vector that points from location to mouse
    acceleration = mousepos - location;
    // Set magnitude of acceleration
    acceleration.normalize();    
    acceleration *= 0.2;
    
    velocity += acceleration;
    velocity.limit(topspeed);
    
    location += velocity;
}

void Mover::checkEdges() {
    
    if (location.x > ci::app::getWindowWidth() ) {
        location.x = 0;
    }
    else if (location.x < 0) {
        location.x = ci::app::getWindowWidth();
    }
    
    if (location.y > ci::app::getWindowHeight() ) {
        location.y = 0;
    }
    else if (location.y < 0) {
        location.y = ci::app::getWindowHeight();
    }
}


void Mover::display() {
    // enable alpha blending
//    ci::gl::enableAlphaBlending();
    ci::gl::color( mColor );
    ci::gl::drawSolidCircle(location, 24.);
//    ci::gl::disableAlphaBlending();    
}