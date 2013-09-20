//
//  Mover.h
//  
//
//  Created by Armin H. on 8/27/13.
//
//

#ifndef __NOC_1_9_motion101_acceleration__Mover__
#define __NOC_1_9_motion101_acceleration__Mover__

#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"

#endif /* defined(__NOC_1_9_motion101_acceleration__Mover__) */


class Mover {
    
public:
    Mover();
    
    ci::Vec2f location;
    ci::Vec2f velocity;
    ci::Vec2f acceleration;
    float mass; // The object's virtual mass
    ci::Vec2f mouse; // mouse position
    ci::ColorA mColor;
    std::list<ci::Vec2f> mHistory; // mover's history
    
    void init();
    void update();
    void apply_force(ci::Vec2f);
    void checkEdges();
    void display();
    void display_history();
};