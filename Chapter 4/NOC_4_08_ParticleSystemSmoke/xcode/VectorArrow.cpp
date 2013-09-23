//
//  VectorArrow.cpp
//  NOC_4_08_ParticleSystemSmoke
//
//  Created by Armin H. on 9/22/13.
//
//

#include "VectorArrow.h"


VectorArrow::VectorArrow( ci::Vec2f vector, ci::Vec2f origin, float scale) {
    mVector = vector;
    mOrigin = origin;
    
    mLineWidth = 2.0;
    mArrowSize = 8.0;
    mArrowScale = scale; // scale factor for arrow length
}

void VectorArrow::update(ci::Vec2f vector) {
    mVector = vector;
}

// adapted from Daniel Shiffman's example (4-8)
void VectorArrow::draw() {
    
    float heading = atan2f(mVector.y, mVector.x);

    gl::pushMatrices();
    gl::translate( mOrigin );
    gl::rotate( toDegrees(heading) );
    
    // Calculate length of vector & scale it to be bigger or smaller if necessary
    float length = mVector.length() * mArrowScale;
    gl::lineWidth( mLineWidth );
    gl::drawLine( ci::Vec2f (0.0, 0.0), ci::Vec2f (length, 0.0 ));
    gl::drawLine( ci::Vec2f (length, 0.0 ), ci::Vec2f (length-mArrowSize, mArrowSize/2) );
    gl::drawLine( ci::Vec2f (length, 0.0 ), ci::Vec2f (length-mArrowSize, -mArrowSize/2) );
 
    gl::popMatrices();    
}