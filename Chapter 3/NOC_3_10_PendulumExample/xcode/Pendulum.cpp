//
//  Pendulum.cpp
//  NOC_3_10_PendulumExample
//
//  Created by Armin H. on 9/13/13.
//
//

#include "Pendulum.h"


Pendulum::Pendulum( ci::Vec2f origin, float r) {
    
    mOrigin = origin;
    mRadius = r;
    
    mAngleVelocity = 0.0;
    mAngleAcceleration = 0.0;
    mDamping = 0.995;   // Arbitrary damping
    mBallRadius = 48.0; // Arbitrary ball radius
    
    mAngle = M_PI_4;
    
}



void Pendulum::go( ci::Vec2f mousepos) {
    update();
    drag( mousepos );
    draw();
}

void Pendulum::update() {
    // As long as we aren't dragging the pendulum, let it swing!
    if (!mDragging) {
        // Calculate acceleration (see: http://www.myphysicslab.com/pendulum1.html)        
        
        mAngleAcceleration = (-1 * mGravity / mRadius) * ci::math<float>::sin( mAngle );
        mAngleVelocity += mAngleAcceleration;             // Increment velocity
        mAngleVelocity *= mDamping;                       // Arbitrary damping
        mAngle += mAngleVelocity;                         // Increment angle
    }
}

void Pendulum::clicked(ci::Vec2f mousepos) {
    // This checks to see if we clicked on the pendulum ball
    ci::Vec2f dvec = mLocation - mousepos;
    float dist = dvec.length();
    if ( dist < mBallRadius ) {
        mDragging = TRUE;
    }
}


void Pendulum::drag(ci::Vec2f mousepos) {
    // If we are draging the ball, we calculate the angle between the
    // pendulum origin and mouse location
    // we assign that angle to the pendulum
    if (mDragging) {
        ci::Vec2f diff = mOrigin - mousepos;                      // Difference between 2 points
        mAngle = ci::math<float>::atan2(-1*diff.y, diff.x) - ci::toRadians(90.);     // Angle relative to vertical axis
    }
}

void Pendulum::stopdragging() {
    mAngleVelocity = 0.0;   // No velocity once you let go
    mDragging = FALSE;
}

    
void Pendulum::draw() {
    
    mLocation.set( ci::Vec2f ( mRadius * ci::math<float>::sin(mAngle),
                               mRadius * ci::math<float>::cos( mAngle )) );
    
    mLocation += mOrigin; // Make sure the location is relative to the pendulum's origin
    
    ci::gl::enableAlphaBlending();
    // Draw the arm
    ci::gl::color(0.f, .6f, .4f, 0.6f);
    ci::gl::drawLine(mOrigin, mLocation);
    
    // Draw the ball
    if (mDragging) {
        ci::gl::color(0.f, .6f, .4f, 1.f);
    }
    ci::gl::drawSolidCircle(mLocation, mBallRadius);
    
    
    ci::gl::disableAlphaBlending();
    

}