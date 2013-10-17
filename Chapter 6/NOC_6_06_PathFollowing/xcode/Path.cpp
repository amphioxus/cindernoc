//
//  Path.cpp
//  NOC_6_06_PathFollowing
//
//  Created by Armin H. on 10/8/13.
//
//

#include "Path.h"

using namespace ci;

Path::Path() {
    if (!mVerts.empty()) {
        mVerts.clear();
    }
    mRadius = 20; // default radius
}


Path::Path(  std::vector< ci::Vec2f > pathVerts, float radius ) {
    
    mVerts = pathVerts;
    mRadius = radius;
    
    triangleStripOutline();    
}

float Path::getRadius() { return mRadius; }

void Path::addVertex( ci::Vec2f vert) {
    mVerts.push_back( vert );
}

void Path::resetLine( std::vector<ci::Vec2f> pathVerts ) {
    if (!mVerts.empty()) {
        mVerts.clear();
    }
    
    mVerts = pathVerts;
    triangleStripOutline();
}


void Path::thickenLine() {
    // This function creates an outline with offset mRadius around the path
    // can be used if GL_LINE_LOOP is used to draw it. (Not used in this example,
    // but I'm leaving it here in case I need it later.
    
    std::vector< ci::Vec2f > backLoop; // container for collecting return path vertices
    
    for ( int i = 1; i < mVerts.size()-1; ++i ) {
        
        // get pre and post line segment
        ci::Vec2f line1 = mVerts.at(i) - mVerts.at(i-1);
        ci::Vec2f line2 = mVerts.at(i+1) - mVerts.at(i);
        
        // get normals to line 1
        ci::Vec2f norm = ci::Vec2f ( line1.y, -line1.x ).normalized();
        
        // tangent:
        ci::Vec2f tangent = ( line2.normalized() + line1.normalized() ).normalized();
        
        // miter line is normal of the tangent:
        ci::Vec2f miter = ci::Vec2f ( -tangent.y, tangent.x );
        // correct length =
        float length = mRadius / miter.dot( norm );
        
        // add offset points for very first vertex
        if (i == 1) {
            mVertsOutline.push_back( mVerts.at(i-1) - mRadius * norm );
            mVertsOutline.push_back( mVerts.at(i-1) + mRadius * norm );
        }
        
        mVertsOutline.push_back( mVerts.at(i) + miter * length );
        backLoop.push_back( mVerts.at(i) - miter * length );
        
        if (i == mVerts.size()-2) {
            ci::Vec2f line = mVerts.at(i+1) - mVerts.at(i);
            norm = ci::Vec2f ( line.y, -line.x ).normalized();
            mVertsOutline.push_back( mVerts.at(i+1) + mRadius * norm );
            mVertsOutline.push_back( mVerts.at(i+1) - mRadius * norm );
        }
    }
    
    // add backLoop points to Outline container:
    for (int i = backLoop.size()-1 ; i >= 0; --i) {
        mVertsOutline.push_back( backLoop.at(i));
    }
}



void Path::triangleStripOutline() {
    // This produces a triangle strip mesh that follows the line and has a
    // thickness of 2*mRadius
    if (!mVertsOutline.empty()) {
        mVertsOutline.clear();
    }
    for ( int i = 1; i < mVerts.size()-1; ++i ) {
        // get pre and post line segment
        ci::Vec2f line1 = mVerts.at(i) - mVerts.at(i-1);
        ci::Vec2f line2 = mVerts.at(i+1) - mVerts.at(i);
        
        // get normals to line 1
        ci::Vec2f norm = ci::Vec2f ( line1.y, -line1.x ).normalized();
        
        // tangent:
        ci::Vec2f tangent = ( line2.normalized() + line1.normalized() ).normalized();
        
        // miter line is normal of the tangent:
        ci::Vec2f miter = ci::Vec2f ( -tangent.y, tangent.x );
        // correct length =
        float length = mRadius / miter.dot( norm );
        // add offset points for very first vertex
        if (i == 1) {
            mVertsOutline.push_back( mVerts.at(i-1) + mRadius * norm );
            mVertsOutline.push_back( mVerts.at(i-1) - mRadius * norm );
        }
        mVertsOutline.push_back( mVerts.at(i) + miter * length );
        mVertsOutline.push_back( mVerts.at(i) - miter * length );
        
        // deal with end of the line:
        if (i == mVerts.size()-2) {
            ci::Vec2f line = mVerts.at(i+1) - mVerts.at(i);
            norm = ci::Vec2f ( line.y, -line.x ).normalized();
            mVertsOutline.push_back( mVerts.at(i+1) + mRadius * norm );
            mVertsOutline.push_back( mVerts.at(i+1) - mRadius * norm );
        }
    }
}


ci::Vec2f Path::intersection( ci::Vec2f p1, ci::Vec2f p2, ci::Vec2f p3, ci::Vec2f p4 ) {
    
    // code from http://flassari.is/2008/11/line-line-intersection-in-cplusplus/

    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return ci::Vec2f (NULL, NULL);

    // Get the x and y coords
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

    // Check if the x and y coordinates are within both lines
    if ( x < std::min(x1, x2) || x > std::max(x1, x2) ||
        x < std::min(x3, x4) || x > std::max(x3, x4) ) return ci::Vec2f (NULL, NULL);
    if ( y < std::min(y1, y2) || y > std::max(y1, y2) ||
        y < std::min(y3, y4) || y > std::max(y3, y4) ) return ci::Vec2f (NULL, NULL);
    
    // Return the point of intersection
    return ci::Vec2f (x, y);
}


void Path::draw() {
    glLineStipple(1, 0xF0F0);
    
    gl::enableAlphaBlending();
    // create GL_POLYGON of path with thickness mRadius
    glLineWidth( 1. );
    gl::color(.7, .7, 0.7);
    
    gl::begin( GL_TRIANGLE_STRIP );
    for (ci::Vec2f v : mVertsOutline ) {
        gl::vertex( v );
    }
    gl::end();
    
    
    // draw actual path vertices
    gl::enable(GL_LINE_STIPPLE);
    gl::lineWidth(2.0);
    gl::color(.2, .2, .2);
    gl::begin( GL_LINE_STRIP );
    for (ci::Vec2f v : mVerts ) {
        gl::vertex( v );
    }
    gl::end();
    gl::disable(GL_LINE_STIPPLE);
    gl::color(0, 0, 0);
    for (ci::Vec2f v : mVerts ) {
        gl::drawSolidCircle( v , 5.f );
    }
    
    
    gl::disableAlphaBlending();
 
}