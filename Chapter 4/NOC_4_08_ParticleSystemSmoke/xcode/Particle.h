//
//  Particle.h
//  NOC_4_07_ParticleSystemForcesRepeller
//
//  Created by Armin H. on 9/15/13.
//
//

#pragma once
#include <iostream>
#include "cinder/Rand.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"

class Particle {
    
    float mLifeSpan;
    float mMass = 1;

    
public:
    Particle( ci::Vec2f, ci::gl::Texture );
    
    ci::Vec2f mLocation;
    ci::Vec2f mVelocity;
    ci::Vec2f mAcceleration;
    
    void applyForce( ci::Vec2f );
    bool isDead();
    void run();     // convenience method to update and draw
    void update();  // Method to update location
    void draw();
    
    ci::gl::Texture mTexture;
    ci::Vec2f mTextureLocation;
};