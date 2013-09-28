//
//  Particle.h
//  NOC_5_6_DistanceJoint
//
//  Created by Armin H. on 9/27/13.
//
//

#pragma once
#include <iostream>
#include "Box2D.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "Scale.h"

class Particle {
    
    float mX, mY, mRadius;
    b2World * mWorld;

    box2d::Scale scale;
    
    ci::Vec2f mLocation;
    float mAngle;
    
public:
    Particle(float x, float y, float r, b2World &world);
    Particle(ci::Vec2f location, float r, b2World &world);
    
    b2Body * mBody;
    
    void makeBody();
    void update();
    void draw();
    
    ci::Vec2f getLocation();
    bool isDead();
    ~Particle();
    
};