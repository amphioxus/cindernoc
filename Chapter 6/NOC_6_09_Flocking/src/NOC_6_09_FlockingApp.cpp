/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 6-9: Flocking
 
 */


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Flock.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_6_09_FlockingApp : public AppNative {
    Flock * mFlock;
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void NOC_6_09_FlockingApp::setup()
{
    mFlock = new Flock();
    // Add an initial set of boids into the system
    for (int i = 0; i < 200; i++) {
        mFlock->addBoid( new Boid( ci::Vec2f( getWindowWidth()/2, getWindowHeight()/2) ) );
    }
}

void NOC_6_09_FlockingApp::mouseDown( MouseEvent event )
{
}

void NOC_6_09_FlockingApp::update()
{
    mFlock->update();
}

void NOC_6_09_FlockingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 1, 1, 1 ) );
    mFlock->draw();
}

CINDER_APP_NATIVE( NOC_6_09_FlockingApp, RendererGl )
