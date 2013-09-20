//
//  Mover.h
//  NOC_1_8_motion101_acceleration
//
//  Created by Armin H. on 8/27/13.
//
//

#ifndef __NOC_1_8_motion101_acceleration__Mover__
#define __NOC_1_8_motion101_acceleration__Mover__

#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"

#endif /* defined(__NOC_1_8_motion101_acceleration__Mover__) */


class Mover {
    
public:
    Mover();
    
    ci::Vec2f location;
    ci::Vec2f velocity;
    ci::Vec2f acceleration;
    float topspeed;
    
    void init();
    void update();
    void checkEdges();
    void display();
    
};