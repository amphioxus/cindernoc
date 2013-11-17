//
//  Segment.cpp
//  NOC_8_09_LSystem
//
//  Created by Armin H. on 11/16/13.
//
//

#include "Segment.h"


Segment::Segment( ci::Vec2f startP, ci::Vec2f endP ) {
    mStart = startP;
    mEnd = endP;
}

void Segment::draw() {
//    ci::gl::drawSolidCircle(mStart, 4.0);
    ci::gl::drawLine( mStart, mEnd );
}