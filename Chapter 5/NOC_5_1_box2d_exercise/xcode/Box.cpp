//
//  Box.cpp
//  NOC_5_1_box2d_exercise
//
//  Created by Armin H. on 9/22/13.
//
//

#include "Box.h"



Box::Box() {
    
}

Box::Box( ci::Vec2f location ) {
    mDims = ci::Vec2f (15, 15); // defines w and h of box
    mLocation = location;
    mRect = ci::Rectf (  mLocation.x  -  mDims.x,
                         mLocation.y  +  mDims.y,
                         mLocation.x  +  mDims.x,
                         mLocation.y  -  mDims.y );
    
    
}

void Box::draw() {
    
    ci::gl::enableAlphaBlending();
    
    ci::gl::color(.6, .6, .6);
    ci::gl::drawSolidRect( mRect );
    ci::gl::color(0., 0., 0.);
    ci::gl::lineWidth( mLinewidth );
    ci::gl::drawStrokedRect( mRect );
    
    ci::gl::disableAlphaBlending();
}