//
//  Windmill.h
//  NOC_5_7_RevoluteJoint
//
//  Created by Armin H. on 9/28/13.
//
//

#pragma once
#include <iostream>
#include "Box2d.h"
#include "cinder/app/AppBasic.h"
#include "cinder/CinderMath.h"
#include "Box.h"
#include "Scale.h"

class Windmill {
  
    b2World * mWorld;
    Box * mBox1;
    Box * mBox2;
    ci::Vec2f mLocation;
    b2RevoluteJoint * mJoint;
    box2d::Scale scale;
    
public:
    Windmill( ci::Vec2f location, b2World &world);
    
    void toggleMotor();
    bool motorOn();
    void update();
    void draw();
};