//
//  Vehicle.h
//  NOC_6_01_Seek
//
//  Created by Armin H. on 10/3/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"

class Vehicle {
protected:
    ci::Vec2f mLocation;
    ci::Vec2f mVelocity;
    ci::Vec2f mAcceleration;
    std::deque<ci::Vec2f> mHistoryTrail;
    float mR;
    float maxForce;
    float maxSpeed;
    float mMass = 1;
    float mTheta;
    int mHistoryLength = 100;
    
public:
    Vehicle( ci::Vec2f location );
    
    void update();
    void seek( ci::Vec2f target );
    void boundaries( ci::Rectf );
    void applyForce( ci::Vec2f force );
    void draw();
    void drawHistory();
};