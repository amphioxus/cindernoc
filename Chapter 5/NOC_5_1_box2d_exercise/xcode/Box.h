//
//  Box.h
//  NOC_5_1_box2d_exercise
//
//  Created by Armin H. on 9/22/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"

class Box {
public:
    Box();
    Box( ci::Vec2f );
    
    ci::Vec2f mLocation;
    ci::Rectf mRect;
    ci::Vec2f mDims;
    float mLinewidth = 2.0;
    void draw();
    
};