//
//  Pendulum.h
//  NOC_3_10_PendulumExample
//
//  Created by Armin H. on 9/13/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/CinderMath.h"

class Pendulum {
public:
    Pendulum( ci::Vec2f origin, float r);
    
    ci::Vec2f mLocation;        // Location of pendulum ball
    ci::Vec2f mOrigin;          // Location of arm origin
    
    float mRadius;              // Length of arm
    float mAngle;               // Pendulum arm angle
    float mAngleVelocity;       // Angle velocity
    float mAngleAcceleration;   // Angle acceleration
    float mBallRadius;          // Ball radius
    float mDamping;             // Arbitary damping amount
    bool  mDragging = false;
    const float mGravity = 0.4;  // Arbitrary constant
    
    void go( ci::Vec2f mousepos );
    void update();
    void clicked( ci::Vec2f mousepos );
    void drag( ci::Vec2f mousepos );
    void stopdragging();
    void draw();
};