//
//  KochFractal.h
//  NOC_8_05_Koch
//
//  Created by Armin H. on 11/4/13.
//
//  A class to manage the list of line segments in the snowflake pattern


#pragma once
#include <iostream>
#include "KochLine.h"


class KochFractal {
    int mCount;
public:
    KochFractal();
    ~KochFractal();
    
    std::vector< KochLine * > mLines;
    ci::Vec2f mStart, mEnd;
    
    void restart();
    void nextLevel();
    std::vector < KochLine * > iterate( std::vector < KochLine * > );
    int  getCount();
    void draw();
};