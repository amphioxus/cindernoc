//
//  Boundary.cpp
//  NOC_5_2_Boxes
//
//  Created by Armin H. on 9/23/13.
//
//

#include "Boundary.h"

Boundary::Boundary(float x, float y, float w, float h,  b2World & world) {
    
    scale.setPointsPerMeter( 100. );
    
    mX = x;
    mY = y;
    mW = w;
    mH = h;
    
//    std::cout << "set X: " << mX << "Y: " << mY << std::endl; // debug
    
    mRect = ci::Rectf(-mW/2, mH/2, mW/2, -mH/2);
    mWorld = & world;
    
    b2BodyDef bodyDef = b2BodyDef();
    bodyDef.type = b2BodyType::b2_staticBody; // create a static body
     // set the body's position:
    bodyDef.position.Set(scale.toPhysics(mX), scale.toPhysics(mY));
    // create the body from the definitions inside our world:
    mBody = mWorld->CreateBody( &bodyDef );
    
    // Create the shape
    b2PolygonShape pShape = b2PolygonShape();
    pShape.SetAsBox( scale.toPhysics( mW/2 ), scale.toPhysics( mH/2 ) );
    
    // Create a fixture to attach shape to body
    b2FixtureDef fixDef = b2FixtureDef();
    fixDef.shape = & pShape;
    mBody->CreateFixture( &fixDef );    
}

void Boundary::draw() {
    
    ci::gl::enableAlphaBlending();
    
    ci::gl::pushMatrices();    
    ci::gl::translate( ci::Vec2f (mX, mY) );
    ci::gl::color(1., 0., 0., .6);
    // We've moved to the center location of the rectangle already:
    ci::gl::drawSolidRect( mRect );

    ci::gl::popMatrices();    
    ci::gl::disableAlphaBlending();

}

