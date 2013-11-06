//
//  KochLine.cpp
//  NOC_8_05_Koch
//
//  Created by Armin H. on 11/4/13.
//
//

#include "KochLine.h"


KochLine::KochLine( ci::Vec2f start, ci::Vec2f end ) {
    mStart = start;
    mEnd = end;    
}


ci::Vec2f KochLine::getStart() { return mStart; }

ci::Vec2f KochLine::getEnd() { return mEnd; }

// This is easy, just 1/3 of the way
ci::Vec2f KochLine::kochLeft() {
    ci::Vec2f v = mEnd - mStart;
    return v/3 + mStart;
}

// More complicated, have to use a little trig to figure out where this PVector is!
ci::Vec2f KochLine::kochMiddle() {
    ci::Vec2f v = (mEnd - mStart)/3;
    ci::Vec2f p = v;
    v.rotate( ci::toRadians(-60.f) );
    v = mStart + p + v;
    return v;
}

// Easy, just 2/3 of the way
ci::Vec2f KochLine::kochRight() {
    ci::Vec2f v = mStart - mEnd;
    return v/3 + mEnd;
}

void KochLine::draw( int recD ) {
    float radius = 6. - recD;
    ci::gl::color(1, 0, 0);
    ci::gl::drawLine( mStart, mEnd );
    if (radius > 1 ) {
        ci::gl::color(1, 1, 1);
        ci::gl::drawSolidCircle(mStart, radius );
        ci::gl::drawSolidCircle(mEnd, radius );
    }
}


// Destructor
KochLine::~KochLine() {
    std::cout << "kochLine destructor called" << std::endl;
}