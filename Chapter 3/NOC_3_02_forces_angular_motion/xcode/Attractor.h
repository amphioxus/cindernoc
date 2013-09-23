//
//  Attractor.h
//  NOC_2_6_attraction
//
//  Created by Armin H. on 8/29/13.
//
//
#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "Mover.h"

class Attractor {
public:
    Attractor();
    Attractor(ci::Vec2f location, float mass);
    
    ci::Vec2f mLocation;
    float mMass;
    ci::ColorA mColor;
    float mG = 1.5;
    bool mRollover = FALSE;
    bool mClicked = FALSE;
    
    ci::Vec2f attract(Mover * m);
    void hover( ci::Vec2f mousepos );
    void clicked( ci::Vec2f mousepos );
    void mouseup();
    void dragged( ci::Vec2f mousepos );
    void set_G(float g);
    void draw();
};