//
//  Box.cpp
//  NOC_5_1_box2d_exercise
//
//  Created by Armin H. on 9/22/13.
//
//

#include "Box.h"

Box::Box( ci::Vec2f location,  float w, float h, bool lock, b2World & world ) {
    
    mDims = ci::Vec2f (w, h );    // defines w and h of box as (w,h)
    mLocation = location;  // location is defined as center of box
    mAngle = 0.;
    
    mRect = ci::Rectf (  -mDims.x/2,
                         mDims.y/2,
                         mDims.x/2,
                         -mDims.y/2 );
    
    mWorld = & world; // reference to the world
    
    // set up body definition and configure it:
    b2BodyDef bodyDef = b2BodyDef();
    if (lock)
        bodyDef.type = b2BodyType::b2_staticBody;
    else
        bodyDef.type = b2BodyType::b2_dynamicBody; // create a dynamic body
    // set the body's position:
    bodyDef.position.Set( scale.toPhysics( mLocation.x ),
                          scale.toPhysics( mLocation.y ) );
    // create the body from the definitions inside our world:
    mBody = mWorld->CreateBody( &bodyDef );
    
    // Give it some initial random velocity
    if (!lock) {
         mBody->SetAngularVelocity( ci::randFloat(-5.f, 5.f) );
    }
       
    // Create the shape (see p.201 in NOC for Processing equivalent)
    b2PolygonShape pShape = b2PolygonShape();
    
    float box2Dw = scale.toPhysics( mDims.x/2 );
    float box2Dh = scale.toPhysics( mDims.y/2 );
    
    pShape.SetAsBox(box2Dw, box2Dh);
    
    // Create a fixture to attach shape to body
    b2FixtureDef fixtureDef = b2FixtureDef();
    fixtureDef.shape = &pShape;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 0.5;
    fixtureDef.density = 1.0;
    
    // Attach the shape to the body with the fixture
    mBody->CreateFixture( &fixtureDef );
    
//    std::cout << "box created at " << mLocation << std::endl; // debug
    
}


void Box::update() {
    // get current position and angle from the Box2D object:    
    b2Vec2 pos = mBody->GetPosition();
    
//    std::cout << "box2d vec: " << pos.x << " / " << pos.y << std::endl; // debug
    
    mLocation.x = scale.fromPhysics (pos.x);
    mLocation.y = scale.fromPhysics (pos.y);
    
    mAngle = mBody->GetAngle();
    
}


void Box::draw() {
    
//    std::cout << "box drawn at " << mLocation << std::endl; // debug
    ci::gl::enableAlphaBlending();    
    ci::gl::pushMatrices();
    
    ci::gl::translate( mLocation );
    ci::gl::rotate( ci::toDegrees( mAngle ) );
    
    ci::gl::color(.6, .6, .6);
    ci::gl::drawSolidRect( mRect );
    ci::gl::color(1., 1., 1.);
    ci::gl::lineWidth( mLinewidth );
    ci::gl::drawStrokedRect( mRect );
    
    ci::gl::popMatrices();    
    ci::gl::disableAlphaBlending();
}


bool Box::contains( ci::Vec2f loc ) {
    b2Vec2 b_loc = b2Vec2 ( scale.toPhysics(loc.x),
                            scale.toPhysics(loc.y)  );
    
    b2Fixture* f = mBody->GetFixtureList();
    
    bool inside = f->TestPoint( b_loc );
    return inside;
}


bool Box::isDead(){
    // check for boxes falling through the window bottom
    if (mLocation.y > ci::app::getWindowHeight()) {
        return TRUE;
    } else
        return FALSE;
}


// destructor
Box::~Box() {
    // destroy body from this world when object gets deleted
    mWorld->DestroyBody( mBody );
//    std::cout << "box destroyed" << std::endl; // debug
}

