// Attraction
// Daniel Shiffman <http://www.shiffman.net>

// A class for a draggable attractive body in our world
// Translated for Cinder C++ by Armin Hinterwirth

#include "Attractor.h"

Attractor::Attractor() {
    // position attractor in the middle of the screen by default
    mLocation.x = ci::app::getWindowWidth()/2;
    mLocation.y = ci::app::getWindowHeight()/2;
    mMass = 20;
//    mColor = ci::ColorA(.8f, .6f, .6f, 0.6f);
}

Attractor::Attractor(ci::Vec2f location, float mass) {
    mLocation = location;
    mMass = mass;
//    mColor = ci::ColorA(.8f, .6f, .6f, 0.6f);
}


ci::Vec2f Attractor::attract(Mover m) {
    ci::Vec2f force = mLocation - m.location;   // Calculate direction of force
    float d = force.length(); // Distance between objects
    // Limiting the distance to eliminate "extreme" results for very close or very far objects:
    if (d < 5)
        d = 5.f;
    else if (d > 25)
        d = 25.f;
    
    float strength = (mG * mMass * m.mMass) / (d * d);
    return strength * force.safeNormalized();
}

// The methods below are for mouse interaction
// Detect when hovering over:
void Attractor::hover( ci::Vec2f mousepos ) {
    ci::Vec2f dvec =  mLocation - mousepos;
    float dis = dvec.length();    
    if (dis < mMass)
        mRollover = TRUE;
    else
        mRollover = FALSE;
}

// Detect when clicked
void Attractor::clicked( ci::Vec2f mousepos ) {
    ci::Vec2f dvec =  mLocation - mousepos;
    float dis = dvec.length();
    
    if (dis < mMass) {
        mClicked = TRUE;
    }
    else {
        mClicked = FALSE;
    }
}

// mouse button released
void Attractor::mouseup() {
    mClicked = FALSE;
}

// update position when dragged
void Attractor::dragged( ci::Vec2f mousepos ) {
    ci::Vec2f dvec =  mLocation - mousepos;
    float dis = dvec.length();
    
    if (dis < mMass) {
        mLocation = mousepos;
        mClicked = TRUE;
    }

}

void Attractor::set_G(float g) {
    mG = g;
    std::cout << "G set to " << mG;
}

void Attractor::display() {
    // Turn on additive blending
    ci::gl::enableAlphaBlending();
    // fill color depends on mouse states:
    if (mClicked) {
        mColor = ci::ColorA(0.f, .6f, .4f, 1.f); }
    else if (mRollover) {
        mColor = ci::ColorA(0.f, .6f, .4f, 0.8f);
    } else
    {
        mColor = ci::ColorA(0.f, .6f, .4f, 0.4f);
    }
    
    ci::gl::color( mColor );
    ci::gl::drawSolidCircle(mLocation, mMass );
    ci::gl::disableAlphaBlending();
    
}