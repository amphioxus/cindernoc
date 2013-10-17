/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 5-5: Multi-Shapes
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "Box2d.h"
#include "Boundary.h"
#include "Lollipop.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_5_5_MultiShapesApp : public AppNative {
    std::vector<Boundary *> mBoundaries;
    std::vector<Lollipop *> mLollipops;
  public:
    b2Vec2 gravity = b2Vec2( 0.f, 10.f );
    b2World mWorld = b2World (gravity);
    
    // Values for iterating through time in Box2D world
    const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
    
	void setup();
    void prepareSettings( Settings * settings);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void NOC_5_5_MultiShapesApp::setup()
{
    // create boundary:
    std::vector<ci::Vec2f> s;
    s.push_back(ci::Vec2f(250, 450));
    s.push_back(ci::Vec2f(getWindowWidth()/2, 500));
    s.push_back(ci::Vec2f(getWindowWidth()-100, 400));
    
    mBoundaries.push_back( new Boundary(s, mWorld));
    
    
    // another boundary:
    std::vector<ci::Vec2f> s2;
    s2.push_back(ci::Vec2f(30, 200));
    s2.push_back(ci::Vec2f(150, 300));
    s2.push_back(ci::Vec2f(200, 320));
    
    mBoundaries.push_back( new Boundary(s2, mWorld));
}


void NOC_5_5_MultiShapesApp::prepareSettings(Settings * settings) {
    settings->setWindowSize(800, 600);
}


void NOC_5_5_MultiShapesApp::mouseDown( MouseEvent event )
{
    mLollipops.push_back( new Lollipop( event.getPos(), mWorld) );
}


void NOC_5_5_MultiShapesApp::update()
{
    
    // create particles randomly
    if (randFloat() < 0.05) {
        mLollipops.push_back( new Lollipop( ci::Vec2f(getWindowWidth()/2, 20 ), mWorld));
    }
    
    // Step forward in time:
    mWorld.Step(timeStep, velocityIterations, positionIterations);
    
    for (int i = 0; i < mLollipops.size(); i++) {
        if (mLollipops.at(i)->isDead()) {
            delete mLollipops.at(i);
            mLollipops.erase(mLollipops.begin()+i);
        } else
            mLollipops.at(i)->update();
    }    
}


void NOC_5_5_MultiShapesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    for (auto b : mBoundaries) {
        b->draw();
    }
    
    for (auto l : mLollipops) {
        l->draw();
    }
}

CINDER_APP_NATIVE( NOC_5_5_MultiShapesApp, RendererGl )
