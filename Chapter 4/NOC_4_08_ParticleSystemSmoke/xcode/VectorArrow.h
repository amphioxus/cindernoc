//
//  VectorArrow.h
//  NOC_4_08_ParticleSystemSmoke
//
//  Created by Armin H. on 9/22/13.
//
//  A class to draw an arrow

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/CinderMath.h"

using namespace ci;

class VectorArrow {
    
public:
    VectorArrow( ci::Vec2f, ci::Vec2f, float );
    
    Vec2f mVector; 
    Vec2f mOrigin;  // start point
    float mLineWidth;
    float mArrowSize;
    float mArrowScale; // scale factor to make arrow longer or shorter
    
    void update( ci::Vec2f ); 
    void draw();
    
};
