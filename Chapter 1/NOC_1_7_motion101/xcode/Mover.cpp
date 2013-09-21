//
//  Mover.cpp
//  NOC_1_7_motion101
//
//  Created by Armin H. on 8/27/13.
//
//

#include "Mover.h"


Mover::Mover() {
    ci::Rand::randomize();
    location.x = ci::Rand::randFloat( 800. );
    location.y = ci::Rand::randFloat( 200.);
    velocity.x = ci::Rand::randFloat(-2., 2.);
    velocity.y = ci::Rand::randFloat(-2., 2.);    
}

void Mover::update() {
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