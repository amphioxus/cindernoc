//
//  Windmill.cpp
//  NOC_5_7_RevoluteJoint
//
//  Created by Armin H. on 9/28/13.
//
//

#include "Windmill.h"


Windmill::Windmill( ci::Vec2f location, b2World &world) {
    
    mWorld = &world;
    mLocation = location;
    // Initialize locations of two boxes
    mBox1 = new Box( mLocation + ci::Vec2f(0,-20), 200, 10, FALSE, *mWorld );
    mBox2 = new Box( mLocation, 10, 40, TRUE, *mWorld);
    
     // Define joint as between two bodies
    b2RevoluteJointDef jointDef = b2RevoluteJointDef();
    jointDef.Initialize(mBox1->mBody, mBox2->mBody, mBox1->mBody->GetWorldCenter() );
    
    // Turning on a motor (optional)
    jointDef.motorSpeed = M_2_PI * 6;      // how fast?
    jointDef.maxMotorTorque = 1000.0;  // how powerful?
    jointDef.enableMotor = FALSE;      // is it on?
    jointDef.collideConnected = FALSE;
    
    mJoint = (b2RevoluteJoint *) mWorld->CreateJoint( &jointDef );
}


void Windmill::toggleMotor() {
    // query whether motor is enabled and set it to the opposite
    mJoint->EnableMotor( !mJoint->IsMotorEnabled() );
}


bool Windmill::motorOn() {
    return mJoint->IsMotorEnabled();
}


void Windmill::update() {
    // update box locations:
    mBox1->update();
    mBox2->update();
}


void Windmill::draw() {
    // draw the boxes:
    mBox1->draw();
    mBox2->draw();
    
    // draw the anchor for debug
    
    b2Vec2 anchor = mBox1->mBody->GetWorldCenter();
//    std::cout << scale.fromPhysics( anchor.x ) << " " << scale.fromPhysics( anchor.y ) << std::endl;

    ci::gl::enableAlphaBlending();
    
    ci::gl::color(.2, .2, .2);
    ci::gl::drawSolidCircle(ci::Vec2f( scale.fromPhysics( anchor.x ),
                                       scale.fromPhysics( anchor.y )), 2.5);
    
    ci::gl::disableAlphaBlending();
    
}