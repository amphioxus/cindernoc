/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 6-7: Separation
 
 */


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "Vehicle.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_6_07_SeparationApp : public AppNative {
    
    std::vector< Vehicle * > mVehicles;
    
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseDrag( MouseEvent event );
	void update();
	void draw();
};

void NOC_6_07_SeparationApp::setup()
{
    for (int i=0; i<100; i++) {
        
        mVehicles.push_back( new Vehicle( ci::Vec2f( randInt(0, getWindowWidth() ),
                                                     randInt(0, getWindowHeight() ) ) ) );
    }
}

void NOC_6_07_SeparationApp::mouseDown( MouseEvent event )
{
}

void NOC_6_07_SeparationApp::mouseDrag( MouseEvent event ) {
    mVehicles.push_back( new Vehicle ( event.getPos() ) );
}

void NOC_6_07_SeparationApp::update()
{
    for (auto v : mVehicles ) {
        v->separate( mVehicles );
        v->update();
        v->checkBorders();
    }
}


void NOC_6_07_SeparationApp::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    for ( auto v : mVehicles ) {
        v->draw();
    }
}

CINDER_APP_NATIVE( NOC_6_07_SeparationApp, RendererGl )
