//
//  CustomShape.cpp
//  NOC_5_4_Polygons
//
//  Created by Armin H. on 9/25/13.
//
//

#include "CustomShape.h"


CustomShape::CustomShape( std::vector<ci::Vec2f> shape, ci::Vec2f center, b2World &world ) {
    
    mWorld = &world;
    mSurfaceVerts = shape;
    mCenter = center;
    
    makeBody();    
}


void CustomShape::update() {
    // get current position and angle from the Box2D object:
    b2Vec2 pos = mBody->GetPosition();
    mCenter.x = scale.fromPhysics (pos.x);
    mCenter.y = scale.fromPhysics (pos.y);
    
    mAngle = mBody->GetAngle();
//    std::cout << "x/y: " << mCenter << std::endl; // debug
}


void CustomShape::draw() {
    /** For how to get body vertices from Box2D bodies see:
     
     http://stackoverflow.com/questions/6618532/how-to-get-a-fixtures-shapes-points-from-a-body-in-box2d
    
    */
    
    ci::gl::pushMatrices();
    ci::gl::translate( mCenter );
    ci::gl::rotate( ci::toDegrees( mAngle ));
    ci::gl::color(.4, .8, .4, 0.8);
    ci::gl::begin( GL_POLYGON );
    
    // now the harder part: get the vertices from the box2d body:
    for (b2Fixture* f = mBody->GetFixtureList(); f; f = f->GetNext()) {
        b2Shape::Type shapeType = f->GetType();
        
        if (shapeType == b2Shape::e_polygon) {
            b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
            
            for (int i=0; i < polygonShape->GetVertexCount(); i++) {
                b2Vec2 v =  polygonShape->GetVertex(i);
                ci::gl::vertex( scale.fromPhysics(v.x),
                                scale.fromPhysics(v.y) );
            }
        }
         else if (shapeType == b2Shape::e_circle) {
           // b2CircleShape* circleShape = (b2CircleShape*)f->GetShape();
             // this won't happen in this example, but this code shows how to
             // deal with multiple shape types
         } else {
             // do nothing
         }        
    }
    
    ci::gl::end();
    ci::gl::popMatrices();
}


void CustomShape::makeBody() {
    
    // make dynamic b2vec array:
    b2Vec2 *container = new b2Vec2[mSurfaceVerts.size()];
    for (int i = 0; i < mSurfaceVerts.size(); i++) {
//        std::cout << "verts:" << mSurfaceVerts.at(i) << std::endl; // debug
        container[i] = b2Vec2( scale.toPhysics( mSurfaceVerts.at(i).x ) ,
                               scale.toPhysics( mSurfaceVerts.at(i).y ) );
    }
    
    
    // CREATE BODY at mCenter location:
    b2BodyDef bodyDef = b2BodyDef();
    bodyDef.type = b2BodyType::b2_dynamicBody; // create a dynamic body
    bodyDef.position.Set( scale.toPhysics( mCenter.x ),
                          scale.toPhysics( mCenter.y ));
    mBody = mWorld->CreateBody( &bodyDef );
    
    // Create the shape (see p.201 in NOC for Processing equivalent)
    b2PolygonShape pShape = b2PolygonShape();
    pShape.Set(container, mSurfaceVerts.size() );
    delete container;
    
    // CREATE FIXTURE:
    b2FixtureDef fixtureDef = b2FixtureDef();
    fixtureDef.shape = &pShape;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 0.5;
    fixtureDef.density = 1.0;

    mBody->CreateFixture( &fixtureDef );
    
    // Give it some initial random velocity
    mBody->SetAngularVelocity( ci::randFloat(-5.f, 5.f) );
    mBody->SetLinearVelocity( b2Vec2 (ci::randFloat(-2.f, 2.f), ci::randFloat(-2.f, 2.f)) );

}



bool CustomShape::isDead() {
    // check for particles falling through the window bottom
    if (mCenter.y > ci::app::getWindowHeight()) {
        return TRUE;
    } else
        return FALSE;
}


CustomShape::~CustomShape(){
    // destroy body from this world when object gets deleted
    mWorld->DestroyBody( mBody );
//    std::cout << "body destroyed" << std::endl; // debug
}

