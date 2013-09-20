//
//  Spring.cpp
//  NOC_3_11_spring
//
//  Created by Armin H. on 9/14/13.
//
//

#include "Spring.h"
using namespace ci;

Spring::Spring( ci::Vec2f anchor, float restlength ) {
    mAnchor = anchor;
    mRestlength = restlength;
}

 // Calculate spring force
void Spring::connect(Bob *bob) {    
    // Vector pointing from anchor to bob location
    ci::Vec2f force = bob->mLocation - mAnchor;
    // What is distance
    // Stretch is difference between current distance and rest length
    float stretch = force.length() - mRestlength;
    // Calculate force according to Hooke's Law
    // F = k * stretch
    bob->applyForce( force.safeNormalized() * -1 * mSpringConstant * stretch );

}


void Spring::constrainLength(Bob * bob, float minlength, float maxlength) {
    // Constrain the distance between bob and anchor between min and max
    ci::Vec2f dir = bob->mLocation - mAnchor;
    float d = dir.length();
    // Is it too short?
    if (d < minlength) {
        // Reset location and stop from moving (not realistic physics)
        bob->mLocation = mAnchor + dir.safeNormalized() * minlength;
        bob->mVelocity *= 0;
    }
    // Is it too long?
    else if (d > maxlength) {
        // Reset location and stop from moving (not realistic physics)
        bob->mLocation = mAnchor + dir.safeNormalized() * maxlength;
        bob->mVelocity *= 0;
    }
}

void Spring::drawAnchor() {
    ci::Rectf arect = ci::Rectf(-10, -10, 10, 10);
    gl::color(0.68, 0.68, 0.68, 0.8);
    
    gl::pushMatrices();
    gl::translate(mAnchor);
    gl::drawSolidRect(arect);
    gl::popMatrices();
}



void Spring::drawLine(Bob * bob) {
    
    gl::lineWidth(3.0);
    gl::color(0.68, 0.68, 0.68, 0.4);
    gl::drawLine( mAnchor, bob->mLocation );
}
