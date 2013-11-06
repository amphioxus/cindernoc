//
//  KochFractal.cpp
//  NOC_8_05_Koch
//
//  Created by Armin H. on 11/4/13.
//
//

#include "KochFractal.h"


KochFractal::KochFractal() {
    mStart = ci::Vec2f(20, ci::app::getWindowHeight()-100);
    mEnd = ci::Vec2f( ci::app::getWindowWidth()-20, ci::app::getWindowHeight()-100);
    restart();
}


KochFractal::~KochFractal() {
    
}


void KochFractal::restart() {
    mCount = 0; // reset counter
    mLines.clear(); // clear the container holding the Koch lines
    mLines.push_back( new KochLine(mStart, mEnd) ); // Add the initial line
}


void KochFractal::nextLevel() {
    // for every line, create 4 more
//    std::vector< KochLine *> swapContainer;
//    swapContainer = iterate( mLines );
    mLines = iterate( mLines );
//    mLines.swap(swapContainer); // quick hack... there must be a better way... Hey, I'm not sure I need it after all. Seems like I can just update mLines with the output from the iterate function... How this affects memory, I have no idea...
    mCount++; // keep track of iteration depth
}


// This is where the **MAGIC** happens
// Step 1: Create an empty vector
// Step 2: For every line currently in the vector
//   - calculate 4 line segments based on Koch algorithm
//   - add all 4 line segments into the new vector
// Step 3: Return the new vector and it becomes the list of line segments for the structure
std::vector < KochLine * > KochFractal::iterate(  std::vector < KochLine * > in ) {
    
    std::vector< KochLine *> out;
    ci::Vec2f a, b, c, d, e;
    
    for (auto l : in ) {
        // Calculate 5 koch lines (done for us by the line object)
        a = l->getStart();
        b = l->kochLeft();
        c = l->kochMiddle();
        d = l->kochRight();
        e = l->getEnd();
        
        // Make line segments between all the PVectors and add them
        out.push_back( new KochLine(a,b) );
        out.push_back( new KochLine(b,c) );
        out.push_back( new KochLine(c,d) );
        out.push_back( new KochLine(d,e) );
    }
    return out;
}


int KochFractal::getCount() {
    return mCount;
}


void KochFractal::draw() {
    
    for (auto line : mLines ) {
        line->draw( mCount );
    }
}