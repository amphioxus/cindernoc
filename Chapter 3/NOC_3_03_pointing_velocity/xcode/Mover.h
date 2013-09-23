//
//  Mover.h
//  
//
//  Created by Armin H. on 8/27/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"
#include "cinder/CinderMath.h"

class Mover {
    
public:
    Mover();
    Mover(float x, float y);
    // position:
    ci::Vec2f mLocation;
    ci::Vec2f mVelocity;
    ci::Vec2f mAcceleration;
    // angular position:
    float mTheta;
    ci::Rectf mRect = ci::Rectf(-20,8,20,-8);
    float mTopspeed = 6.0;
//    float mMass; // The object's virtual mass
    ci::ColorA mColor;
    std::deque<ci::Vec2f> mHistory; // mover's history
    float mG = 1; // gravitational constant
    
//    void init();
    void update( ci::Vec2f mousepos );
//    ci::Vec2f attract( Mover * m );
//    void applyForce( ci::Vec2f force );
    void checkEdges();
    void draw();
    void draw_history();
};