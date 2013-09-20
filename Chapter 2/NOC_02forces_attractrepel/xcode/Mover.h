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
#include "cinder/CinderMath.h"
#include "math.h"


// create type alias for shared pointer to mover object:
typedef std::shared_ptr<class Mover> MoverRef;

class Mover {
    
public:
	
	Mover();
    Mover(float m, float x, float y);
	
	void update( ci::Vec2f mousepos );
	void draw();
    void draw_history();
    void applyForce(ci::Vec2f force);
    void checkEdges();
    ci::Vec2f attract(MoverRef m);
    
    ci::Vec2f mLocation, mVelocity, mAcceleration;
    std::deque<ci::Vec2f> mLocationHistory;
    float mMass;
    const float topspeed = 8.0;
};