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
        
    topspeed = 6;
}

void Mover::update() {
    acceleration = ci::Rand::randVec2f(); // random vector along unit circle
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
    
    ci::gl::color( 1.0f, 0.5f, 0.25f );
    
    ci::gl::drawSolidCircle(location, 24.);
    
    
}