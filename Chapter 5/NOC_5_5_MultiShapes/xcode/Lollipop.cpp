//
//  Lollipop.cpp
//  NOC_5_5_MultiShapes
//
//  Created by Armin H. on 9/26/13.
//
//

#include "Lollipop.h"



Lollipop::Lollipop( ci::Vec2f center, b2World &world) {
    
    mWorld = &world;
    mCenter = center;
    
    mW = 8.0;
    mH = 24.0;
    mRadius = 8;
    
    makeBody();
    
}


void Lollipop::makeBody() {
    
    mRect = ci::Rectf(-mW/2, mH/2, mW/2, -mH/2); // for drawing rectangle
    
    // CREATE BODY at mCenter location:
    b2BodyDef bodyDef = b2BodyDef();
    bodyDef.type = b2BodyType::b2_dynamicBody;            // create a dynamic body
    bodyDef.position.Set( scale.toPhysics( mCenter.x ),
                          scale.toPhysics( mCenter.y ) );
    mBody = mWorld->CreateBody( &bodyDef );
    
    b2CircleShape cShape = b2CircleShape();
    cShape.m_radius = scale.toPhysics( mRadius );
    cShape.m_p.Set( 0,
                    scale.toPhysics(-mH/2));
    
    // CREATE RECTANGLE SHAPE
    b2PolygonShape rShape = b2PolygonShape();
    rShape.SetAsBox( scale.toPhysics( mW/2),
                     scale.toPhysics( mH/2));
    

    // CREATE FIXTURES:
    // Create a fixture to attach shape to body
    // Rectangle first:
    b2FixtureDef fixtureDef = b2FixtureDef();
    fixtureDef.shape = &rShape;
    // Parameters that affect physics
    fixtureDef.density = 1;
    fixtureDef.friction = 0.01;
    fixtureDef.restitution = 0.3;
    // Attach the shape to the body with the fixture
    mBody->CreateFixture( &fixtureDef );
    
    
    b2FixtureDef fixtureDef2 = b2FixtureDef();
    fixtureDef2.shape = &cShape;
    // Parameters that affect physics
    fixtureDef2.density = 1;
    fixtureDef2.friction = 0.01;
    fixtureDef2.restitution = 0.3;
    // Attach the shape to the body with the fixture
    mBody->CreateFixture( &fixtureDef2 );

    // shortcut for creating fixtures:
//    mBody->CreateFixture( &rShape, 1.0);
//    mBody->CreateFixture( &cShape, 1.0);
    
    // Give it some initial random velocity
    mBody->SetAngularVelocity( ci::randFloat(-5.f, 5.f) );
    mBody->SetLinearVelocity( b2Vec2 (ci::randFloat(-2.f, 2.f), ci::randFloat(-2.f, 2.f)) );


}


void Lollipop::update() {
    b2Vec2 pos = mBody->GetPosition();
    mCenter = ci::Vec2f (scale.fromPhysics(pos.x),
                         scale.fromPhysics(pos.y)); // transform position to ci::vector
    mAngle = mBody->GetAngle();
    
}

void Lollipop::draw() {
    
    ci::gl::enableAlphaBlending();
    ci::gl::pushMatrices();
    
    ci::gl::translate( mCenter );
    ci::gl::rotate( ci::toDegrees( mAngle ) );
    
    // draw rectangle:
    ci::gl::color(0., .6, .5, .5);
    ci::gl::drawSolidRect( mRect );
    ci::gl::color(1, 1, 1);
    ci::gl::drawStrokedRect( mRect );
    // draw circle
    ci::gl::color(0., .6, .5, .5);
    ci::gl::drawSolidCircle( ci::Vec2f(0,-mH/2), mRadius );
    ci::gl::color(1, 1, 1);
    ci::gl::drawStrokedCircle( ci::Vec2f(0,-mH/2), mRadius );
    
    ci::gl::popMatrices();
    ci::gl::disableAlphaBlending();
    
}


bool Lollipop::isDead() {
    // check for pops falling through the window bottom
    if (mCenter.y > ci::app::getWindowHeight()) {
        return TRUE;
    } else
        return FALSE;

}


Lollipop::~Lollipop() {
    // destroy body from this world when object gets deleted
    mWorld->DestroyBody( mBody );
}
