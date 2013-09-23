// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)

// Example 3-10: Pendulum

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Pendulum.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_3_10_PendulumExampleApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void mouseUp( MouseEvent event );
	void update();
	void draw();
    
    Pendulum *pendulum;
    
    ci::Vec2f mMousePos;
};


void NOC_3_10_PendulumExampleApp::setup()
{
    // Make a new Pendulum with an origin location and armlength
    pendulum  = new Pendulum( ci::Vec2f( getWindowWidth()/2, 0), 300 );
    setFrameRate(60.);
}


void NOC_3_10_PendulumExampleApp::mouseDown( MouseEvent event )
{
    mMousePos = event.getPos();
    pendulum->clicked( mMousePos );
}

void NOC_3_10_PendulumExampleApp::mouseDrag( MouseEvent event ) {
    mMousePos = event.getPos();
    pendulum->drag( mMousePos );
}

void NOC_3_10_PendulumExampleApp::mouseUp( MouseEvent event )
{
    pendulum->stopdragging();
}

void NOC_3_10_PendulumExampleApp::update()
{
    pendulum->drag( mMousePos );
    pendulum->update();
    
}


void NOC_3_10_PendulumExampleApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    pendulum->draw();
}

CINDER_APP_NATIVE( NOC_3_10_PendulumExampleApp, RendererGl )
