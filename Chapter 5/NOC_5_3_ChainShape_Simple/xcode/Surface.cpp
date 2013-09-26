//
//  Surface.cpp
//  NOC_5_3_ChainShape_Simple
//
//  Created by Armin H. on 9/24/13.
//
//

#include "Surface.h"

using namespace box2d;

Surface::Surface( std::vector<ci::Vec2f> surface, b2World &world) {
    mWorld = &world;
    mSurfaceVerts = surface;
    
    // make dynamic b2vec array:
    b2Vec2 *container = new b2Vec2[surface.size()];
    for (int i = 0; i < surface.size(); i++) {
        container[i] = b2Vec2( scale.toPhysics( mSurfaceVerts.at(i).x ) ,
                               scale.toPhysics( mSurfaceVerts.at(i).y ) );
    }

    // CREATE BODY:    
    b2BodyDef bodyDef = b2BodyDef();
    // body def doesn't need type (static by default for chains), nor position
    // create the body from the definitions inside our world:
    mBody = mWorld->CreateBody( &bodyDef );
    
    // CREATE SHAPE:
    b2ChainShape chainShape = b2ChainShape();
    chainShape.CreateChain(container, surface.size());
    delete container;
    
    // CREATE FIXTURE:
    b2FixtureDef fixtureDef = b2FixtureDef();
    fixtureDef.shape = &chainShape;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 0.5;
    fixtureDef.density = 1.0;
    
    // Attach the shape to the body with the fixture
    mBody->CreateFixture( &fixtureDef );
    
    
}

void Surface::draw() {    
    ci::PolyLine<ci::Vec2f> pline;
    for (ci::Vec2f v : mSurfaceVerts) {
        pline.push_back( v );
    }    
    ci::gl::color(0., .6, .5, .5);
    ci::gl::draw( pline );
}

