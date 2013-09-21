//
//  Mover.cpp
//
//  Created by Armin H. on 8/27/13.
//
//

#include "Mover.h"


Mover::Mover() {
    
//    ci::Rand::randomize();
    location.x = 30.0; location.y = 30.;
    velocity.x = 0.;  velocity.y = 0.;
    acceleration.x = 0;  acceleration.y = 0;
    mass = 1;
    
    mColor = ci::ColorA(1.0f, 0.5f, 0.25f, 1.f);
}

void Mover::update() {
    mHistory.push_back(location); // remember position
    if (mHistory.size() > 100){
        mHistory.pop_front();
    }
    velocity += acceleration;
    location += velocity;
    
    acceleration *= 0; // set acceleration to zero
}


void Mover::apply_force(ci::Vec2f force) {
    force /= mass;
    acceleration += force;
}


void Mover::checkEdges() {
    
    if (location.x > ci::app::getWindowWidth() ) {
        location.x = ci::app::getWindowWidth();
        velocity.x *= -1;
    }
    else if (location.x < 0) {
        location.x = 0;
        velocity.x *= -1;
    }
    
    if (location.y > ci::app::getWindowHeight() ) {
        location.y = ci::app::getWindowHeight();
        velocity.y *= -1;
    }
}


void Mover::display() {
    // Turn on additive blending
    ci::gl::enableAlphaBlending();
    ci::gl::color( mColor );
    ci::gl::drawSolidCircle(location, 24.);
    ci::gl::disableAlphaBlending();
}


void Mover::display_history() {
    // Turn on additive blending
    ci::gl::enableAlphaBlending();
    ci::gl::color( ci::ColorA(.8f, .6f, .6f, 0.6f) );
    // iterate through history of each mover
    for (auto h : mHistory) {
        ci::Vec2f pos (h.x, h.y);
        ci::gl::drawSolidCircle(pos, 1.5);
    }
    
    ci::gl::disableAlphaBlending();
}