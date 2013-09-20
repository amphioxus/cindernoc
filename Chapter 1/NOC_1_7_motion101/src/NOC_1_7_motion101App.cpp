// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 1-7: Motion 101

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 200;

class NOC_1_7_motion101App : public AppNative {
  public:
    void prepareSettings( Settings *settings );
    void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    Mover mover; // declaration already creates a Mover object
    
};


void NOC_1_7_motion101App::prepareSettings( Settings *settings )
{
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
}

void NOC_1_7_motion101App::setup()
{
}


void NOC_1_7_motion101App::mouseDown( MouseEvent event )
{
}

void NOC_1_7_motion101App::update()
{
    mover.update();
    mover.checkEdges();
}

void NOC_1_7_motion101App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    mover.display();
    
}

CINDER_APP_NATIVE( NOC_1_7_motion101App, RendererGl )
