//
//  Particle.h
//  NOC_5_3_Exercise_WaveChain
//
//  Created by Armin H. on 9/24/13.
//
//

#pragma once
#include <iostream>
#include "Box2d.h"
#include "Scale.h"
#include "cinder/Rand.h"

class Particle {
    
    float mX, mY, mRadius;
    b2World * mWorld;
    b2Body * mBody;
    box2d::Scale scale;
    
    ci::Vec2f mLocation;
    float mAngle;
    
public:
    Particle(int x, int y, float r, b2World &world);
    Particle(ci::Vec2f location, float r, b2World &world);
    
    void makeBody();
    void update();
    void draw();
    
    bool isDead();
    ~Particle();
    
};