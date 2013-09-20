//
//  Spring.h
//  NOC_3_11_spring
//
//  Created by Armin H. on 9/14/13.
//
//

#pragma once
#include <iostream>
#include "Bob.h"


class Spring {
public:
    Spring( ci::Vec2f, float );
    
    ci::Vec2f mAnchor; // Location
    
    // rest length and spring constant:
    float mRestlength;
    float mSpringConstant = 0.2;
    
    void connect( Bob * );
    void constrainLength( Bob *, float, float);
    void drawAnchor();
    void drawLine( Bob * );
    
};