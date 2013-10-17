//
//  FlowField.h
//  NOC_6_04_Flowfield
//
//  Created by Armin H. on 10/4/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Perlin.h"
#include "cinder/CinderMath.h"
#include "Common.h"

class FlowField {
protected:
    int mResolution;
    int mCols;
    int mRows;
    ci::Perlin *mPerlin;
    ci::Vec2f mNoise;
    
    float mArrowSize;
    
public:
    FlowField( int resolution );
    std::vector< std::vector< ci::Vec2f > > mFlowField;
    void init();
    ci::Vec2f lookup( ci::Vec2f loc );
    void drawVector( ci::Vec2f vec, ci::Vec2f loc );
    void drawGrid();
    void draw();
};