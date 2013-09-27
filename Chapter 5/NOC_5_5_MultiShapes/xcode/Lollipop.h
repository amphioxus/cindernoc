//
//  Lollipop.h
//  NOC_5_5_MultiShapes
//
//  Created by Armin H. on 9/26/13.
//
//

#pragma once
#include <iostream>
#include "Box2d.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "Scale.h"

class Lollipop {
    
public:
    Lollipop(  ci::Vec2f center, b2World &world );
    
    b2World *mWorld;
    b2Body *mBody;
    box2d::Scale scale;
    ci::Rectf mRect;     // box rectangle for drawing
    ci::Vec2f mCenter;
    float mH, mW; // Height and width of lollipop
    float mRadius;
    float mAngle;
    
    void makeBody();
    void update();
    void draw();
    bool isDead();
    
    ~Lollipop();
    
};