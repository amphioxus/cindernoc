//
//  Segment.h
//  NOC_8_09_LSystem
//
//  Created by Armin H. on 11/16/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"

class Segment {
protected:
    ci::Vec2f mStart, mEnd; // start and end points of the segment line
public:
    Segment( ci::Vec2f startP, ci::Vec2f endP );
    void draw();
    
};