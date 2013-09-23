// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)

// Example 3-11: Spring

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Bob.h"
#include "Spring.h"



using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_3_11_springApp : public AppNative {
    
    const ci::Vec2f mGravity = ci::Vec2f (0., 2.);
    ci::Vec2f mMousePos;
    
  public:
    
    Bob *bob; // pointer to Bob
    Spring *spring; // pointer to spring    
    
    void prepareSettings( Settings *settings);
	void setup();
	void mouseDown( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void mouseUp( MouseEvent event );
	void update();
	void draw();
};

void NOC_3_11_springApp::prepareSettings( Settings *settings ) {
    settings->setWindowSize(800, 600);
    settings->setFrameRate(60.);
}

void NOC_3_11_springApp::setup()
{
    bob = new Bob( ci::Vec2f ( getWindowWidth()/2, 2*getWindowHeight()/3) );
    spring = new Spring( ci::Vec2f (getWindowWidth()/2 , 10), getWindowHeight()/2 );
}

void NOC_3_11_springApp::mouseDown( MouseEvent event )
{
    mMousePos = event.getPos();
    bob->clicked( mMousePos );
}

void NOC_3_11_springApp::mouseDrag( MouseEvent event ) {
    mMousePos = event.getPos();
}

void NOC_3_11_springApp::mouseUp( MouseEvent event ) {
    bob->stopDragging();
}

void NOC_3_11_springApp::update()
{
    bob->applyForce( mGravity );
    spring->connect( bob );
    spring->constrainLength( bob , 30, 500);
    bob->update();
     bob->drag( mMousePos );
}

void NOC_3_11_springApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    spring->drawAnchor();
    spring->drawLine( bob );
    bob->draw();
    
}

CINDER_APP_NATIVE( NOC_3_11_springApp, RendererGl )
