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
//
// Note: Pressing "f" toggles full screen mode
// You can add "movers" by pressing "a", and delete individual ones by pressing "x".
// Pressing 'c' deletes the whole bunch...


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class NOC_1_11_motion101_acceleration_arrayApp : public AppNative {
  public:
    void prepareSettings( Settings *settings );
    void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseDrag (MouseEvent event );
    void keyDown (KeyEvent event);
	void update();
	void draw();
    
    std::list<Mover> movers; // C++ list to store Mover objects
    
    ci::Vec2f mouse; // store mouse position
};


void NOC_1_11_motion101_acceleration_arrayApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
    settings->setTitle("Motion 101: multiple Mover objects");
}

void NOC_1_11_motion101_acceleration_arrayApp::setup()
{
    // create 20 Mover objects
    for (int i = 0; i < 20; i++ ) {
        movers.push_back( Mover() );
    }
}


void NOC_1_11_motion101_acceleration_arrayApp::mouseDown( MouseEvent event )
{
}

void NOC_1_11_motion101_acceleration_arrayApp::mouseMove( MouseEvent event )
{
    mouse = event.getPos();
}

void NOC_1_11_motion101_acceleration_arrayApp::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}

void NOC_1_11_motion101_acceleration_arrayApp::keyDown(KeyEvent event)
{
    if( event.getChar() == 'f' ) {
        // Toggle between full-screen and window:
        setFullScreen( ! isFullScreen() );
    }
    else if (event.getChar() == 'a') {
        movers.push_back( Mover() );
    } 
    else if (event.getChar() == 'x') {
        movers.pop_back();
    }
    else if (event.getChar() == 'c') {
        // clear the whole list
        movers.clear();
    }
		
}

void NOC_1_11_motion101_acceleration_arrayApp::update()
{
}

void NOC_1_11_motion101_acceleration_arrayApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    // Turn on additive blending
	gl::enableAlphaBlending();
    // iterate through all the Movers in the list:
    for ( std::list<Mover>::iterator it = movers.begin(); it != movers.end(); it++)
    {
        it->update(mouse);
        it->display();
    }
    gl::disableAlphaBlending();
    
}

CINDER_APP_NATIVE( NOC_1_11_motion101_acceleration_arrayApp, RendererGl )
