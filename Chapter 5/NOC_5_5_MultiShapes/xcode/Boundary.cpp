//
//  Boundary.cpp
//  NOC_5_3_ChainShape_Simple
//
//  Created by Armin H. on 9/24/13.
//
//

#include "Boundary.h"


Boundary::Boundary( std::vector<ci::Vec2f> boundary, b2World &world) {
    mWorld = &world;
    mBoundaryVerts = boundary;
    
    // make dynamic b2vec array:
    b2Vec2 *container = new b2Vec2[boundary.size()];
    for (int i = 0; i < boundary.size(); i++) {
        container[i] = b2Vec2( scale.toPhysics( mBoundaryVerts.at(i).x ) ,
                               scale.toPhysics( mBoundaryVerts.at(i).y ) );
    }

    // CREATE BODY:    
    b2BodyDef bodyDef = b2BodyDef();
    // body def doesn't need type (static by default for chains), nor position
    // create the body from the definitions inside our world:
    mBody = mWorld->CreateBody( &bodyDef );
    
    // CREATE SHAPE:
    b2ChainShape chainShape = b2ChainShape();
    chainShape.CreateChain(container, boundary.size());
    delete container;
    
    // CREATE FIXTURE:
    b2FixtureDef fixtureDef = b2FixtureDef();
    fixtureDef.shape = &chainShape;
    fixtureDef.friction = 0.9;
    fixtureDef.restitution = 0.5;
    fixtureDef.density = 1.0;
    
    // Attach the shape to the body with the fixture
    mBody->CreateFixture( &fixtureDef );

    
}

void Boundary::draw() {    
    ci::PolyLine<ci::Vec2f> pline;
    for (ci::Vec2f v : mBoundaryVerts) {
        pline.push_back( v );
    }    
    ci::gl::color(0., .6, .5, .5);
    ci::gl::draw( pline );
}

