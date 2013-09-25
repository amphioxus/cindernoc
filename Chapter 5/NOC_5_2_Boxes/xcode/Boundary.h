//
//  Boundary.h
//  NOC_5_2_Boxes
//
//  Created by Armin H. on 9/23/13.
//
//

#pragma once
#include <iostream>
#include "Box2d.h"
#include "Scale.h"

class Boundary {
    
public:
    Boundary(float x, float y, float w, float h, b2World & world);
    
    box2d::Scale scale; // to make conversions easier
    b2World * mWorld;
    b2Body * mBody;
    float mX, mY, mW, mH;
    ci::Rectf mRect;

    void draw();
};