//
//  CA.cpp
//  NOC_7_01_WolframCA_simple
//
//  Created by Armin H. on 10/28/13.
//
//

#include "CA.h"


CA::CA() {
    init();
}


void CA::init() {
    mHcells = ci::app::getWindowWidth() / mW;  // number of horizontal cells
    mVcells = ci::app::getWindowHeight() / mW; // number of vertical cells
    // set the size of 2D array:
    mCells.resize(mVcells);
    for (int i = 0; i < mVcells; ++i) {
        mCells[i].resize(mHcells);
    }
    
    // set all cells to zero
    for (int i = 0; i < mVcells; i++) {
        for (int j = 0; j < mHcells; j++) {
            mCells[i][j] = 0;
        }
    }
    
    // We arbitrarily start with just the middle cell (of first row) having a state of "1"
    mCells[0][mHcells/2]= 1;
    
    mGeneration = 0; // set the generation number to zero
    
}


 // The process of creating the new generation
void CA::generate() {
    if (mGeneration < mVcells-1 ) {
        // allocate array for holding calculated next generation
        int nextgen[ mHcells ];
        // put zeros in the array:
        for (int i = 0; i < mHcells-1; i++) {
            nextgen[i] = 0;
        }
        
        // For every spot, determine new state by examing current state, and neighbor states
        // Ignore edges that only have one neighor
        for (int i = 1; i < mHcells-2; i++) {
            int left = mCells[mGeneration][i-1];  // Left neighbor state
            int me = mCells[mGeneration][i];      // Current state
            int right = mCells[mGeneration][i+1]; // Right neighbor state
            nextgen[i] = rules(left, me, right);  // Compute next generation state based on ruleset
        }
        // The current generation is the new generation
        for (int i = 0; i < mHcells-1; i++) {
            mCells[mGeneration+1][i] = nextgen[i];
        }
//        std::cout << mGeneration << std::endl; // debug
        mGeneration++;
    }
}


// Implementing the Wolfram rules
// Could be improved and made more concise, but here we can explicitly see what is going on for each case
int CA::rules(int a, int b, int c) {
    if (a == 1 && b == 1 && c == 1) return mRuleset[0];
    if (a == 1 && b == 1 && c == 0) return mRuleset[1];
    if (a == 1 && b == 0 && c == 1) return mRuleset[2];
    if (a == 1 && b == 0 && c == 0) return mRuleset[3];
    if (a == 0 && b == 1 && c == 1) return mRuleset[4];
    if (a == 0 && b == 1 && c == 0) return mRuleset[5];
    if (a == 0 && b == 0 && c == 1) return mRuleset[6];
    if (a == 0 && b == 0 && c == 0) return mRuleset[7];
    return 0;
}


void CA::draw() {
    
    ci::Rectf box;
    
    for (int i = 0; i < mVcells; i++) {
        
        for (int j = 0; j < mHcells; j++) {
            
            if (mCells[i][j] == 1 ) {
                ci::gl::color(1, 1, 1);
            } else {
                ci::gl::color(0, 0, 0);
            }
            // draw a box for each cell:
            box = ci::Rectf( ci::Vec2f(j*mW, i*mW),
                             ci::Vec2f(j*mW + mW, i*mW + mW ) );
            ci::gl::drawSolidRect( box );
            // debug: draw the grid
            if ( mDrawgrid ) {
                ci::gl::color(1, 0, 0);
                ci::gl::drawStrokedRect( box );
            }
        }
    }
}



