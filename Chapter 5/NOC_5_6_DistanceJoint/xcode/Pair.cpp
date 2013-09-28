//
//  Pair.cpp
//  NOC_5_6_DistanceJoint
//
//  Created by Armin H. on 9/27/13.
//
//

#include "Pair.h"


Pair::Pair( ci::Vec2f location, b2World &world ) {
    
//    p1 = new Particle ();
    mWorld = &world;
    mLocation = location;
   
    mP1 = new Particle ( mLocation , 8.0, *mWorld );
//    mP2 = new Particle ( mLocation + ci::Vec2f( ci::randFloat(-1,1), ci::randFloat(-1,1) ),
//                         8.0,
//                        *mWorld );
    mP2 = new Particle ( mLocation + ci::Vec2f( ci::randFloat(-10,10), ci::randFloat(-10,10) ),
                        8.0,
                        *mWorld );
    b2DistanceJointDef distDef = b2DistanceJointDef();
    distDef.length = mLength;
    distDef.bodyA = mP1->mBody;
    distDef.bodyB = mP2->mBody;
    distDef.length = scale.toPhysics( mLength );
    
    // These properties affect how springy the joint is
    distDef.frequencyHz = 3.;  // Try a value less than 5 (0 for no elasticity)
    distDef.dampingRatio = 0.1; // Ranges between 0 and 1 (1 for no springiness)
    
    // create the joint:
    mJoint = mWorld->CreateJoint( &distDef );
//    mWorld->CreateJoint( &distDef );
}


bool Pair::isDead() {
    // if particle 1 and 2 are both offscreen, mark pair for deletion
    if ( mLocation.y > 800) {
//        std::cout << "isDead TRUE" << std::endl;
        return TRUE;
    } else
        return FALSE;    
}


void Pair::update() {
    mLocation = mP1->getLocation();
    // get updated particle positions:
    mP1->update();
    mP2->update();
}


void Pair::draw() {    
    // draw the spring:
    ci::gl::enableAlphaBlending();
    
    ci::gl::color(.2, .2, .2);
    // draw line from mP1 to mP2
    ci::gl::lineWidth(3.0);
    ci::gl::drawLine( mP1->getLocation(), mP2->getLocation() );
    
    ci::gl::disableAlphaBlending();
    // draw the particles:
    mP1->draw();
    mP2->draw();    
}


Pair::~Pair() {
    mWorld->DestroyJoint( mJoint );
    delete mP1;
    delete mP2;
//    std::cout << "joint destroyed" << std::endl; // debug
}

