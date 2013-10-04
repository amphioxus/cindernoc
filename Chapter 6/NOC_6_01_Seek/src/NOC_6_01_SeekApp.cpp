#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Vehicle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_6_01_SeekApp : public AppNative {
    Vehicle * mVehicle;
    ci::Vec2f mMousePos;
  public:
	void setup();
    void prepareSettings( Settings * settings);
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
	void draw();
};

void NOC_6_01_SeekApp::setup()
{
    mVehicle = new Vehicle( ci::Vec2f( getWindowHeight()/2, getWindowHeight()/2) );
}

void NOC_6_01_SeekApp::prepareSettings(Settings * settings) {
//    settings->setFrameRate(20);
}

void NOC_6_01_SeekApp::mouseDown( MouseEvent event )
{
}

void NOC_6_01_SeekApp::mouseMove( MouseEvent event )
{
    mMousePos = event.getPos();
}

void NOC_6_01_SeekApp::update()
{
    mVehicle->seek( mMousePos );
    mVehicle->update();
    
}

void NOC_6_01_SeekApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    ci::gl::enableAlphaBlending();
    ci::gl::color(.8, .2, .2, .6);
    ci::gl::drawSolidCircle(mMousePos, 12.0);
    
    ci::gl::disableAlphaBlending();
    
    mVehicle->draw();
}

CINDER_APP_NATIVE( NOC_6_01_SeekApp, RendererGl )
