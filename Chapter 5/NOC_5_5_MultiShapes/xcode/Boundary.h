//
//  Boundary.h
//  NOC_5_3_ChainShape_Simple
//
//  Created by Armin H. on 9/24/13.
//
//

#pragma once
#include <iostream>
#include "Box2d.h"
#include "Scale.h"

//namespace box2d
//{

class Boundary {
    std::vector<ci::Vec2f> mBoundaryVerts;
    
public:
    Boundary( std::vector<ci::Vec2f> boundary, b2World &world); // constructor for vertex list supplied as cinder vector vector
    b2World *mWorld;
    b2Body *mBody;
    box2d::Scale scale;
    
    void draw();
};

// }