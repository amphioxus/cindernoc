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
    location.x = ci::Rand::randFloat( ci::app::getWindowWidth() );
    location.y = ci::Rand::randFloat( ci::app::getWindowHeight() );
    velocity.x = 0.;  velocity.y = 0.;
    acceleration.x = 0;  acceleration.y = 0;
    mMass = ci::Rand::randFloat(0.5, 2.);
    mColor = ci::ColorA(1.0f, 0.5f, 0.25f, 0.3f);
}


Mover::Mover(float m, float x, float y) {
    
//    ci::Rand::randomize();
    location.x = x; location.y =y;
    velocity.x = 0.;  velocity.y = 0.;
    acceleration.x = 0;  acceleration.y = 0;
    mMass = m;
    
//    mColor = ci::ColorA(0.8, .4, .4, .5);
    mColor = ci::ColorA(1.0f, 0.5f, 0.25f, 0.3f);
}

void Mover::update() {
    mHistory.push_back(location); // remember position
    if (mHistory.size() > 200){
//        mHistory.pop_back();
        mHistory.pop_front();
    }
    
    velocity += acceleration;
    location += velocity;
    
    acceleration *= 0; // set acceleration to zero after each cycle
}

ci::Vec2f Mover::attract(Mover m) {
    
    ci::Vec2f force = location - m.location;     // Calculate direction of force
    float distance = force.length();             // Distance between objects
    // Limiting the distance to eliminate "extreme" results for very close or very far objects:
    if ( distance < 5.0 )
        distance = 5.0;
    else if (distance > 25.0)
        distance = 25.0;
    
    float strength = (mG * mMass * m.mMass) / (distance * distance); // Calculate gravitional force magnitude
    
    return force.safeNormalized() * strength;   // Get force vector --> magnitude * direction

}


void Mover::apply_force(ci::Vec2f force) {
    force /= mMass;
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
    ci::gl::drawSolidCircle(location, mMass * 16.f);
    ci::gl::disableAlphaBlending();
}


void Mover::display_history() {
    // Turn on additive blending
    ci::gl::enableAlphaBlending();
    ci::gl::color( ci::ColorA(.8f, .6f, .6f, 0.6f) );
    // iterate through history of each mover
    for (std::list<ci::Vec2f>::iterator it = mHistory.begin(); it != mHistory.end(); it++) {

        ci::Vec2f pos (it->x, it->y);
        ci::gl::drawSolidCircle(pos, 1.5);
    }
    ci::gl::disableAlphaBlending();
}