//
//  Particle.cpp
//  NOC_5_6_DistanceJoint
//
//  Created by Armin H. on 9/27/13.
//
//

#include "Particle.h"


Particle::Particle(float x, float y, float r, b2World &world) {
    mWorld = &world; // World needs to know about this particle
    
    mLocation = ci::Vec2f (x, y);
    mRadius = r;
    
    makeBody(); // create the Box2D body
}


Particle::Particle(ci::Vec2f location, float r, b2World &world) {
    mWorld = &world; // World needs to know about this particle
    
    mLocation = location;
    mRadius = r;
    
    makeBody(); // create the Box2D body
}


void Particle::makeBody() {
    // set up body definition and configure it:
    b2BodyDef bodyDef = b2BodyDef();
    bodyDef.type = b2BodyType::b2_dynamicBody; // create a dynamic body
    // set the body's position:
    bodyDef.position.Set( scale.toPhysics( mLocation.x ),
                         scale.toPhysics( mLocation.y ) );
    // create the body from the definitions inside our world:
    mBody = mWorld->CreateBody( &bodyDef );
    
    // Give it some initial random velocity
//    mBody->SetAngularVelocity( ci::randFloat(-5.f, 5.f) );
//    mBody->SetLinearVelocity( b2Vec2 (ci::randFloat(-2.f, 2.f), ci::randFloat(-2.f, 2.f)) );
//
    b2CircleShape cShape = b2CircleShape();
    cShape.m_radius = scale.toPhysics( mRadius );
    
    // Create a fixture to attach shape to body
    b2FixtureDef fixtureDef = b2FixtureDef();
    fixtureDef.shape = &cShape;
    // Parameters that affect physics
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 0.3;
    
    // Attach the shape to the body with the fixture
    mBody->CreateFixture( &fixtureDef );
    
}


void Particle::update() {
    // get current position and angle from the Box2D object:
    b2Vec2 pos = mBody->GetPosition();
    mLocation.x = scale.fromPhysics (pos.x);
    mLocation.y = scale.fromPhysics (pos.y);
    
    mAngle = mBody->GetAngle();
}


void Particle::draw() {    
    ci::gl::enableAlphaBlending();
    ci::gl::pushMatrices();
    
    ci::gl::translate( mLocation );
    ci::gl::rotate( -1*ci::toDegrees( mAngle ) );
    
    ci::gl::color(.4, .4, .4, 0.8);
    ci::gl::drawSolidCircle( ci::Vec2f(0,0), mRadius );
    ci::gl::lineWidth(3.0);
    ci::gl::color(0, 0, 0);
    ci::gl::drawStrokedCircle( ci::Vec2f(0,0), mRadius );
//    ci::gl::color(.8, .8, .8);
    // draw line to show angular orientation:
    ci::gl::drawLine(ci::Vec2f(0,0), ci::Vec2f(0, mRadius));
    ci::gl::popMatrices();
    ci::gl::disableAlphaBlending();    
}


ci::Vec2f Particle::getLocation() { return mLocation; }


bool Particle::isDead(){
    // check for particles falling through the window bottom
    if (mLocation.y > ci::app::getWindowHeight()) {
        return TRUE;
    } else
        return FALSE;
}


Particle::~Particle() {
    // destroy body from this world when object gets deleted
    mWorld->DestroyBody( mBody );
//    std::cout << "particle destroyed" << std::endl; // debug
}




