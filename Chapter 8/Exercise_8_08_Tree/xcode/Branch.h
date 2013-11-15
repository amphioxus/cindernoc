//
//  Branch.h
//  NOC_8_07_TreeStochastic
//
//  Created by Armin H. on 11/14/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"

using namespace ci;

class Branch {
protected:
    Vec2f mStartP, mEndP;  // Start and end points of the branch
    float mThickness;      // thickness of the branch
    float mLength;         // length of this branch
    float mTheta;          // direction of branch
    const float mLredux = 0.66;   // length reduction factor for each new branch
    int mHierarchy;        // where we are in brach hierarchy
public:
    Branch( Vec2f start, Vec2f end , int bLevel );
    ~Branch();
    
    Branch* branch( float angle );
    int getHierarchy();
    void draw();
};