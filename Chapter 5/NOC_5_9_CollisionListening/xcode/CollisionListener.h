//
//  CollisionListener.h
//  NOC_5_9_CollisionListening
//
//  Created by Armin H. on 10/2/13.
//
//

#pragma once
#include <iostream>
#include "Box2d.h"
#include "Particle.h"

class CollisionListener : public b2ContactListener {
    // Called when two fixtures begin to touch
    virtual void BeginContact(b2Contact* contact);
    
    // Called when two fixtures cease to touch
    virtual void EndContact(b2Contact* contact);
};
