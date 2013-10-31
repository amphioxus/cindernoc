//
//  CA.h
//  NOC_7_01_WolframCA_simple
//
//  Created by Armin H. on 10/28/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"

class CA {
public:
    CA();
    std::vector< std::vector <int> > mCells; // An array of 0s and 1s. Implemented as a 2D std::vector container to make it easier to allocate array dynamically.
    int mRuleset[8] = {0, 1, 0, 1, 1, 0, 1, 0}; // An array to store the ruleset, for example {0,1,1,0,1,1,0,1}
    int mW = 10; // width of each cell in pixel
    int mHcells;
    int mVcells;
    int mGeneration; // How many generations?
    bool mDrawgrid = false;
    void generate();
    void init();
    int rules(int a, int b, int c);
    void draw();
};