//
//  Liquid.h
//  NOC_2_5_fluidresistance
//
//  Created by Armin H. on 8/28/13.
//
//

#pragma once

#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Color.h"
#include "Mover.h"

class Liquid {
    
public:
    Liquid();
    Liquid(float x, float y, float w, float h, float const c);
    
    // Liquid is a rectangle
    float mX, mY, mW, mH;
    // Coefficient of drag
    float mC;
    ci::ColorA mColor;
    
    bool contains(Mover m);
    ci::Vec2f drag(Mover m);
    void resize(float x, float y, float w, float h);
    void display();
};