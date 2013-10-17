/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 5-6: Distance Joints
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Box2d.h"
#include "Boundary.h"
#include "Particle.h"
#include "Pair.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_5_6_DistanceJointApp : public AppNative {
    
    std::vector<Boundary *> mBoundaries;
    std::vector<Pair *> mPairs; // particle pair object
    
    // Values for iterating through time in Box2D world
    const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
    
  public:
    b2Vec2 gravity = b2Vec2( 0.f, 10.f );
    b2World mWorld = b2World ( gravity );
	void setup();
    void prepareSettings( Settings * settings );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};


void NOC_5_6_DistanceJointApp::setup()
{
    // create boundaries:    
    ci::Rectf b1 = ci::Rectf(20, 400, 420, 410);
    mBoundaries.push_back( new Boundary(b1, 14, mWorld));
    
    ci::Rectf b2 = ci::Rectf(200, 300, 500, 310);
    mBoundaries.push_back( new Boundary(b2, -10, mWorld));
}


void NOC_5_6_DistanceJointApp::prepareSettings( Settings * settings )
{
    settings->setWindowSize(800, 600);
}


void NOC_5_6_DistanceJointApp::mouseDown( MouseEvent event )
{
    mPairs.push_back( new Pair (event.getPos(), mWorld) );
}


void NOC_5_6_DistanceJointApp::update()
{
    // Step forward in time:
    mWorld.Step(timeStep, velocityIterations, positionIterations);

    for (int i = 0; i < mPairs.size(); i++) {
        if (mPairs.at(i)->isDead()){
            delete mPairs.at(i);
            mPairs.erase(mPairs.begin()+i);
        } else
            mPairs.at(i)->update();
    } 
}

void NOC_5_6_DistanceJointApp::draw()
{
	// clear out the window with black
	gl::clear( Color( .8, .8, .8 ) );
    
    for (auto b : mBoundaries) {
        b->draw();
    }
    for (auto p : mPairs) {
        p->draw();
    }
}

CINDER_APP_NATIVE( NOC_5_6_DistanceJointApp, RendererGl )
