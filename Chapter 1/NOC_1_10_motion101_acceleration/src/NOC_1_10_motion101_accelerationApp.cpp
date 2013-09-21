// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 1-10: Motion 101 (acceleration towards the mouse)
//
// Demonstration of the basics of motion with vector.
// A "Mover" object stores location, velocity, and acceleration as vectors
// The motion is controlled by affecting the acceleration (in this case towards the mouse)

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class NOC_1_10_motion101_accelerationApp : public AppNative {
  public:
    void prepareSettings( Settings *settings );
    void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseDrag (MouseEvent event );
	void update();
	void draw();
    
    Mover * mover;
    
    ci::Vec2f mouse; // store mouse position
};


void NOC_1_10_motion101_accelerationApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
}

void NOC_1_10_motion101_accelerationApp::setup()
{
    mover = new Mover();
}


void NOC_1_10_motion101_accelerationApp::mouseDown( MouseEvent event )
{
}

void NOC_1_10_motion101_accelerationApp::mouseMove( MouseEvent event )
{
    mouse = event.getPos();
}

void NOC_1_10_motion101_accelerationApp::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}


void NOC_1_10_motion101_accelerationApp::update()
{
    mover->update(mouse);
//    mover->checkEdges();
}

void NOC_1_10_motion101_accelerationApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    mover->display();
    
}

CINDER_APP_NATIVE( NOC_1_10_motion101_accelerationApp, RendererGl )
