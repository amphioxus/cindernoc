//
//  Cell.h
//  NOC_7_02_GameOfLifeOOP
//
//  Created by Armin H. on 10/31/13.
//
//

#pragma once
#include <iostream>
#include "cinder/Rand.h"

class Cell {
public:
    Cell(float x, float y, float w);
    
    float mX, mY, mW;
    int mStatePrevious, mStateCurrent;
    ci::Rectf mCellbox;
    void newstate(int s);
    void updateDims(float x, float y, float w);
    void reset();
    void savePrevious();
    void draw();
    
    ~Cell();
};


