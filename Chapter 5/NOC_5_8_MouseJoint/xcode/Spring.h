//
//  Spring.h
//  NOC_5_8_MouseJoint
//
//  Created by Armin H. on 9/28/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "Box2d.h"
#include "Box.h"

class Spring {
    
public:
    Spring( b2World &world );
    
    b2World * mWorld;
    b2MouseJoint * mMouseJoint;
    box2d::Scale scale;
    Box *mBox; // pointer to the affiliated box
    
    ci::Vec2f mMouseLoc; // keep track of current mouse location
    void bind( ci::Vec2f mouselocation, Box &box);
    void destroy();
    void update( ci::Vec2f mouselocation );
    void draw();
    
};