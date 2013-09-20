//
//  Bob.h
//  NOC_3_11_spring
//
//  Created by Armin H. on 9/14/13.
//
//

#pragma once
#include <iostream>


class Bob {
public:
    Bob( ci::Vec2f location );
    
    ci::Vec2f mLocation;
    ci::Vec2f mVelocity;
    ci::Vec2f mAcceleration;
    
    const float mMass = 24;
    // Arbitrary damping to simulate friction / drag
    const float mDamping = 0.98;
    
    // For mouse interaction
    bool mDragging = FALSE;
    void clicked( ci::Vec2f );
    void drag( ci::Vec2f );
    void stopDragging();
    
    void update();
    void applyForce( ci::Vec2f force );
    void draw();
};