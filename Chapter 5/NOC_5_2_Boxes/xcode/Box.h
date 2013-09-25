//
//  Box.h
//  NOC_5_2_boxes
//
//  Created by Armin H. on 9/22/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "Box2d.h"
#include "Scale.h"
#include "cinder/Rand.h"

class Box {
       
public:
//    Box();
    Box( ci::Vec2f, b2World &); // create a box within Box2D world
    
    b2Body * mBody;      // reference to Box2D body
    b2World * mWorld;    // reference to the world
    
    box2d::Scale scale;  // convenience class by David Wicks
    
    
    ci::Vec2f mLocation; // box location in pixels
    ci::Rectf mRect;     // box rectangle for drawing
    ci::Vec2f mDims;     // box dimensions
    float mAngle;        // box's angle
    float mLinewidth = 2.0;
    
    void update();
    void draw();
    bool isDead();

    ~Box(); // destructor
};