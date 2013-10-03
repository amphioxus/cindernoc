//
//  Spring.cpp
//  NOC_5_8_MouseJoint
//
//  Created by Armin H. on 9/28/13.
//
//

#include "Spring.h"


Spring::Spring( b2World &world ) {
    
    mMouseJoint = NULL; // set joint to null pointer at first
    mWorld = &world;
    
    
}


void Spring::bind( ci::Vec2f mouselocation, Box &box )
{
    mMouseLoc = mouselocation;
    mBox = &box; 
    b2MouseJointDef mjDef = b2MouseJointDef();
    // Body A is just a fake ground body for simplicity (there isn't anything at the mouse)
    b2BodyDef bd;
    b2Body *groundBody = mWorld->CreateBody(&bd);
    mjDef.bodyA = groundBody;
    
    // Body 2 is the box's boxy
    mjDef.bodyB = box.mBody;
    // Get the mouse location in world coordinates
    // And that's the target
    mjDef.target.Set( scale.toPhysics( mouselocation.x),
                      scale.toPhysics( mouselocation.y)   );
    
    
    // Some stuff about how strong and bouncy the spring should be
    mjDef.frequencyHz = 5.;
    mjDef.dampingRatio = 0.9;
    mjDef.maxForce = 1000.0 * box.mBody->GetMass();
    
    mMouseJoint = (b2MouseJoint*) mWorld->CreateJoint( &mjDef );
    
    
}


void Spring::destroy() {
    if ( mMouseJoint != NULL ) {
        mWorld->DestroyJoint( mMouseJoint );
        mMouseJoint = NULL;
    }    
}


void Spring::update( ci::Vec2f mouselocation ) {
    mMouseLoc = mouselocation;
    if ( mMouseJoint != NULL ) {
        // Always convert to world coordinates!
        b2Vec2 mloc = b2Vec2( scale.toPhysics(mouselocation.x),
                              scale.toPhysics(mouselocation.y) );
        mMouseJoint->SetTarget(mloc);
    }
}


void Spring::draw() {
    if ( mMouseJoint != NULL ) {
        ci::gl::enableAlphaBlending();
        ci::gl::color(.6, .2, .2, .5);
        ci::gl::lineWidth(2.0);
        ci::gl::drawLine(mMouseLoc, mBox->mLocation );
        ci::gl::disableAlphaBlending();       
    }
}




