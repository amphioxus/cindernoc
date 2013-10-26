//
//  Boid.h
//  NOC_6_09_Flocking
//
//  Created by Armin H. on 10/23/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"

class Boid {
protected:
    ci::Vec2f mVelocity;
    ci::Vec2f mAcceleration;
    float mR;
    float mMaxForce;
    float mMaxSpeed;
    float mMass = 1;
    float mTheta;
    
public:
    Boid( ci::Vec2f location);
    
    ci::Vec2f mLocation;
    
    void flock( std::vector< Boid * > boidList );
    void applyBehaviors( std::vector< Boid * > boidList );
    void update();
    ci::Vec2f seek( ci::Vec2f target );
    ci::Vec2f separate( std::vector< Boid * > boidList );
    ci::Vec2f align( std::vector< Boid * > boidList );
    ci::Vec2f cohere( std::vector< Boid * > boidList );
    void applyForce( ci::Vec2f force );
    void checkBorders();
    void draw();
};