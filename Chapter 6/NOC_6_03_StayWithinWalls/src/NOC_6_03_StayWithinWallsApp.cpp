#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Vehicle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_6_03_StayWithinWallsApp : public AppNative {
    float mB = 25; // boundary
    ci::Rectf mRect;
    Vehicle *mVehicle;

  public:
	void setup();
    void prepareSettings( Settings * settings);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void NOC_6_03_StayWithinWallsApp::setup()
{
    mVehicle = new Vehicle( ci::Vec2f(getWindowWidth()/2, getWindowHeight()/2) );
    mRect = ci::Rectf ( mB, mB, getWindowWidth()-mB, getWindowHeight()-mB);
}

void NOC_6_03_StayWithinWallsApp::prepareSettings(Settings * settings) {
    settings->setWindowSize(600, 300);
}

void NOC_6_03_StayWithinWallsApp::mouseDown( MouseEvent event )
{
    delete mVehicle;
    mVehicle = new Vehicle( event.getPos() );
}

void NOC_6_03_StayWithinWallsApp::update()
{
    mVehicle->boundaries( mRect );
    mVehicle->update();
}

void NOC_6_03_StayWithinWallsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    // draw the boundary
    ci::gl::lineWidth(2.0);
    ci::gl::color(.8, .8, .8);
    ci::gl::drawStrokedRect( mRect );
    
    mVehicle->draw();
}

CINDER_APP_NATIVE( NOC_6_03_StayWithinWallsApp, RendererGl )
