//
//  KochLine.h
//  NOC_8_05_Koch
//
//  Created by Armin H. on 11/4/13.
//
//

#pragma once
#include <iostream>
#include "cinder/CinderMath.h"

class KochLine {
    ci::Vec2f mStart;
    ci::Vec2f mEnd;
public:
    KochLine( ci::Vec2f start, ci::Vec2f end );
    ~KochLine();
    
    ci::Vec2f getStart();
    ci::Vec2f getEnd();
    ci::Vec2f kochLeft();
    ci::Vec2f kochMiddle();
    ci::Vec2f kochRight();
    
    void draw( int recD );
};