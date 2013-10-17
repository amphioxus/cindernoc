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
#include "FlowField.h"
#include "Common.h"

class Vehicle {
    FlowField *mFlowField;
protected:
    std::deque<ci::Vec2f> mHistoryTrail;
    int mHistoryLength = 100;
    ci::Vec2f mVelocity;
    ci::Vec2f mAcceleration;
    float mR;
    float mMaxForce;
    float mMaxSpeed;
    float mMass = 1;
    float mTheta;
    
public:
    Vehicle( ci::Vec2f location );
    Vehicle( ci::Vec2f location, float maxSpeed, float maxForce);
    
    ci::Vec2f mLocation;
    bool mDead;
    
    void update();
    
    void follow( FlowField *flow );
    void checkBorders();
    
    void seek( ci::Vec2f target );
    void checkBoundaries( ci::Rectf );
    void applyForce( ci::Vec2f force );
    bool isDead();
    void draw();
    void drawHistory();
};