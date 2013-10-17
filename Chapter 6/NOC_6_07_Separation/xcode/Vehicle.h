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


class Vehicle {
protected:
    ci::Vec2f mVelocity;
    ci::Vec2f mAcceleration;
    float mR;
    float mMaxForce;
    float mMaxSpeed;
    float mMass = 1;
    
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    
public:
    Vehicle( ci::Vec2f location );
    
    ci::Vec2f mLocation;
    
    void update();
    void separate( std::vector< Vehicle * > );
    void checkBorders();
    void applyForce( ci::Vec2f force );
    void draw();
};