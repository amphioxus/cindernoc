//
//  Path.h
//  NOC_6_06_PathFollowing
//
//  Created by Armin H. on 10/8/13.
//
//

#pragma once
#include <iostream>
#include <algorithm>
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Common.h"

class Path {
protected:
    float mRadius;
    std::vector< ci::Vec2f > mVertsOutline; // container for vertices of thick path
//    const int LINE_WIDTH = 2;
    
public:
    Path();
    Path( std::vector< ci::Vec2f > pathVerts, float radius );
    
    std::vector< ci::Vec2f > mVerts; // container to collect path vertices

    float getRadius();
    void addVertex( ci::Vec2f );
    void resetLine( std::vector< ci::Vec2f > pathVerts );
    void thickenLine();
    void triangleStripOutline();
    ci::Vec2f intersection( ci::Vec2f p1, ci::Vec2f p2, ci::Vec2f p3, ci::Vec2f p4 );
    void draw();
};