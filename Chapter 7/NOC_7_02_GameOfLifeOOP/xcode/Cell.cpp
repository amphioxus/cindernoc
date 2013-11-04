//
//  Cell.cpp
//  NOC_7_02_GameOfLifeOOP
//
//  Created by Armin H. on 10/31/13.
//
//

#include "Cell.h"

Cell::Cell(float x, float y, float w) {
    
    mX = x;
    mY = y;
    mW = w;
    
    mStateCurrent = ci::randInt(2);
//    std::cout << mStateCurrent << std::endl;
    mStatePrevious = mStateCurrent;
    // define rectangle for drawing:
    mCellbox = ci::Rectf( ci::Vec2f(x, y),
                         ci::Vec2f(x+w, y+w) );
}

void Cell::updateDims(float x, float y, float w) {
    mX = x;
    mY = y;
    mW = w;
    mCellbox = ci::Rectf( ci::Vec2f(x, y),
                          ci::Vec2f(x+w, y+w) );
}

void Cell::reset() {
    mStateCurrent = ci::randInt(2);
}

void Cell::newstate( int s ) {
    mStateCurrent = s;
}

void Cell::savePrevious() {
    mStatePrevious = mStateCurrent;
}


void Cell::draw() {

    if (mStatePrevious == 0 && mStateCurrent == 1) { // just born
        ci::gl::color(1, 0, 0);
    }
    else if (mStatePrevious == 1 && mStateCurrent == 0) { // just died
        ci::gl::color(0, 0, 1);
    }
    else if ( mStateCurrent == 1) { // alive
        ci::gl::color(1, 1, 1);
    }
    else {
        ci::gl::color(0, 0, 0); // dead
    }
    ci::gl::drawSolidRect( mCellbox );
    
}

Cell::~Cell() {
    
}



