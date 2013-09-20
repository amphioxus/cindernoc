//
//  Confetti.h
//  NOC_4_05_ParticleSystemInheritancePolymorphism
//
//  Created by Armin H. on 9/19/13.
//
//

#pragma once
#include <iostream>
#include "Particle.h"
#include "cinder/CinderMath.h"

class Confetti : public Particle {
    
public:
    Confetti ( ci::Vec2f location );

    ci::Rectf mRect;
   
    virtual void draw(); // draw is virtual method, different function for inherited classes
    
};