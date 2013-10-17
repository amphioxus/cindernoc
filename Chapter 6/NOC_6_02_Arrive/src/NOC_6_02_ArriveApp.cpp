/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 6-2: Arrive steering behavior
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Vehicle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_6_02_ArriveApp : public AppNative {
    Vehicle *mVehicle;
    ci::Vec2f mMousePos;
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
	void draw();
};

void NOC_6_02_ArriveApp::setup()
{
    mVehicle = new Vehicle( ci::Vec2f(getWindowWidth()/2, getWindowHeight()/2) );
}

void NOC_6_02_ArriveApp::mouseDown( MouseEvent event )
{
}

void NOC_6_02_ArriveApp::mouseMove( MouseEvent event ) {
    mMousePos = event.getPos();
}


void NOC_6_02_ArriveApp::update()
{
    mVehicle->seek( mMousePos );
    mVehicle->update();
}

void NOC_6_02_ArriveApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    ci::gl::enableAlphaBlending();
    ci::gl::color(.8, .2, .2, .4);
    ci::gl::drawSolidCircle(mMousePos, 50.0);
    
    ci::gl::disableAlphaBlending();
    
    mVehicle->draw();
}

CINDER_APP_NATIVE( NOC_6_02_ArriveApp, RendererGl )
