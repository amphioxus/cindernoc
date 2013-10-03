//
//  Boundary.cpp
//  NOC_5_3_ChainShape_Simple
//
//  Created by Armin H. on 9/24/13.
//
//

#include "Boundary.h"


Boundary::Boundary ( ci::Rectf bRect, b2World &world ) {
    
    mWorld = &world;
    mRect = bRect;
    float w = mRect.x2 - mRect.x1; // width
    float h = mRect.y2 - mRect.y1; // height
    mCenter = ci::Vec2f ( bRect.x1 + w/2, bRect.y1 + h/2 );
    mAngle = 0;
    makeBody();
}

Boundary::Boundary ( ci::Rectf bRect, float angle, b2World &world ) {
    
    mWorld = &world;
    mRect = bRect;
    float w = mRect.x2 - mRect.x1; // width
    float h = mRect.y2 - mRect.y1; // height
    mCenter = ci::Vec2f ( bRect.x1 + w/2, bRect.y1 + h/2 );
    mAngle = angle;
    makeBody();
}

void Boundary::makeBody() {
    
    // convert mRect location information into Box2D info
    float w = mRect.x2 - mRect.x1; // width
    float h = mRect.y2 - mRect.y1; // height
    
    // center of rectangle:
    b2Vec2 rcenter = b2Vec2 ( mRect.x1 + w/2, mRect.y1 + h/2 );
    
    // CREATE BODY:
    b2BodyDef bodyDef = b2BodyDef();
    bodyDef.position.Set( scale.toPhysics(rcenter.x), scale.toPhysics(rcenter.y));
    bodyDef.angle = ci::toRadians( mAngle );
    bodyDef.type = b2BodyType::b2_staticBody;
    mBody = mWorld->CreateBody( &bodyDef );
    
    // CREATE SHAPE:
    b2PolygonShape rShape = b2PolygonShape();
    rShape.SetAsBox( scale.toPhysics(w/2),
                     scale.toPhysics(h/2));
    
    // CREATE FIXTURE:    
    b2FixtureDef rFixDef = b2FixtureDef();
    rFixDef.shape = &rShape;
    rFixDef.density = 1;
    rFixDef.friction = 0.3;
    
    mBody->CreateFixture( &rFixDef );    
}


void Boundary::draw() {
    ci::Rectf rect = ci::Rectf ( mRect.x1 - mCenter.x,
                                 mRect.y1 - mCenter.y,
                                 mRect.x2 - mCenter.x,
                                 mRect.y2 - mCenter.y);
    ci::gl::pushMatrices();
    ci::gl::translate( mCenter );
    ci::gl::rotate( mAngle );
    
    ci::gl::color(.6, .6, .6, .5);
    ci::gl::drawSolidRect( rect );
    
    ci::gl::popMatrices();
}


Boundary::~Boundary(){
    mWorld->DestroyBody( mBody );
}


