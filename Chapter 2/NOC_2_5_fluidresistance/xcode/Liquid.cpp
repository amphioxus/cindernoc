//
//  Liquid.cpp
//  NOC_2_5_fluidresistance
//
//  Created by Armin H. on 8/28/13.
//
//

#include "Liquid.h"

Liquid::Liquid() {
    
}

Liquid::Liquid(float x, float y, float w, float h, float c) {
    mX = x;
    mY = y;
    mW = w;
    mH = h;
    mC = c;
    
    mColor = ci::ColorA(0.2f, 0.49f, 0.62f, 0.5f);
}

bool Liquid::contains(Mover * m) {
    
    ci::Vec2f l = m->location;
    if (l.x > mX && l.x < mX + mW && l.y > mY && l.y < mY + mH) {
        return TRUE;
    } else {
        return FALSE;
    }
    
}


ci::Vec2f Liquid::drag(Mover * m) {
    
    // Magnitude is coefficient * speed squared
    float speed = m->velocity.length();
    float dragMagnitude = mC * speed * speed;
    
    // Direction is inverse of velocity
    ci::Vec2f dragForce = m->velocity.inverse();
    
    // Scale according to magnitude and return
    return dragForce.safeNormalized() * dragMagnitude;
}

void Liquid::resize(float x, float y, float w, float h) {
    mX = x;
    mY = y;
    mW = w;
    mH = h;
}

void Liquid::display() {
    // Turn on additive blending
    ci::gl::enableAlphaBlending();
    ci::gl::color( mColor );
    ci::Rectf rect (mX, mY, mX + mW, mY + mH);
    ci::gl::drawSolidRect(rect);
    ci::gl::disableAlphaBlending();
    
}