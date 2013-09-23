//
//  Mover.h
//  
//
//  Created by Armin H. on 8/27/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"

class Mover {
    
public:
    Mover();
    Mover(float m, float x, float y);
    
    ci::Vec2f location;
    ci::Vec2f velocity;
    ci::Vec2f acceleration;
    float mMass; // The object's virtual mass
//    ci::Vec2f mouse; // mouse position
    ci::ColorA mColor;
    std::deque<ci::Vec2f> mHistory; // mover's history
    float mG = 1; // gravitational constant
    
    void init();
    void update();
    ci::Vec2f attract( Mover * m );
    void apply_force( ci::Vec2f force );
    void checkEdges();
    void display();
    void display_history();
};