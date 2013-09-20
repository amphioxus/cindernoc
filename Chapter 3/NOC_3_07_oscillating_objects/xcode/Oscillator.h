//
//  Oscillator.h
//  NOC_3_07_oscillating_objects
//
//  Created by Armin H. on 9/12/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"

// reference pointer for keeping track of oscillators
typedef std::shared_ptr<class Oscillator> OscillatorRef;

class Oscillator {
public:
    Oscillator();
    
    ci::Vec2f mAngle, mVelocity, mAmplitude;
    void oscillate();
    void draw();
    
};