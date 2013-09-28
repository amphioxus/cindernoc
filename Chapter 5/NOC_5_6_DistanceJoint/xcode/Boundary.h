//
//  Boundary.h
//  NOC_5_3_ChainShape_Simple
//
//  Created by Armin H. on 9/24/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "Box2d.h"
#include "Scale.h"

//namespace box2d
//{

class Boundary {
    std::vector<ci::Vec2f> mBoundaryVerts;
    ci::Rectf mRect;
    ci::Vec2f mCenter;
    float mAngle;
    
public:
    Boundary( ci::Rectf bRect, b2World &world ); // constructor to create rectangular solid body
    Boundary( ci::Rectf bRect, float angle, b2World &world );  // supply angle as well
    
    b2World *mWorld;
    b2Body *mBody;
    box2d::Scale scale;
    
    void makeBody();
    void draw();
    
    ~Boundary();
};

// }