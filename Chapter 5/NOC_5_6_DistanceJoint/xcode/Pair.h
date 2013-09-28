//
//  Pair.h
//  NOC_5_6_DistanceJoint
//
//  Created by Armin H. on 9/27/13.
//
//

#pragma once
#include <iostream>
#include "cinder/Rand.h"
#include "Box2d.h"
#include "Particle.h"
#include "Scale.h"


class Pair {
    b2World * mWorld;
    
    Particle * mP1;
    Particle * mP2;
    b2Joint * mJoint;
    
    ci::Vec2f mLocation;
    float mRadius;
    float mLength = 32.;
    
    box2d::Scale scale;

public:
    Pair( ci::Vec2f location, b2World &world);
    
    void update();
    void draw();
    
    bool isDead();
    ~Pair();
    
};