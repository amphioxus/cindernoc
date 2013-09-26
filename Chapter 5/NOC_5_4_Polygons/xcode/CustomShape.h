//
//  CustomShape.h
//  NOC_5_4_Polygons
//
//  Created by Armin H. on 9/25/13.
//
//

#pragma once
#include <iostream>
#include "cinder/Rand.h"
#include "Box2d.h"
#include "Scale.h"

class CustomShape {
    
    std::vector< ci::Vec2f > mSurfaceVerts; // vector containing vertex coords
    ci::Vec2f mCenter;
    float mAngle;
    
public:
    CustomShape( std::vector<ci::Vec2f> shape, ci::Vec2f center, b2World &world);
    
    b2World *mWorld;
    b2Body *mBody;
    box2d::Scale scale;
    
    void update();
    void draw();
    void makeBody();
    bool isDead();
    
    ~CustomShape();
};