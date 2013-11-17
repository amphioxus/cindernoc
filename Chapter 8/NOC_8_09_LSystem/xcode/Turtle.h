//
//  Turtle.h
//  NOC_8_09_LSystem
//
//  Created by Armin H. on 11/15/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/CinderMath.h"
#include "Segment.h"

class Turtle {
protected:
    std::string mTodo;
    float mLength;
    float mTheta; // keeps track of current angular orientation
    float mThetaStep; // step size for each rotation instruction (in radians)
    std::vector < Segment * > mSegments;
    ci::Vec2f mCurrentPosition, mLastPosition, mStartpoint;
    std::vector< ci::Vec2f > mRestorePosition;
    std::vector< float > mRestoreAngle;
    
public:
    Turtle( std::string todo, float length, float theta );
    
    void calculatePaths();
    void draw();
    void setLength( float length );
    void changeLength ( float percent );
    void setTodo( std::string todo );
};