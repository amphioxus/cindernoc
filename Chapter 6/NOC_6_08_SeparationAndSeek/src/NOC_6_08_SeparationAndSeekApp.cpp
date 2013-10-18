/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 6-8: Separation and Seek
 
 */


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "Vehicle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_6_08_SeparationAndSeekApp : public AppNative {
    
    std::vector< Vehicle * > mVehicles;
    ci::Vec2f mMousePos;
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseDrag( MouseEvent event );
	void update();
	void draw();
};

void NOC_6_08_SeparationAndSeekApp::setup()
{
    for (int i=0; i<100; i++) {
        
        mVehicles.push_back( new Vehicle( ci::Vec2f( randInt(0, getWindowWidth() ),
                                                     randInt(0, getWindowHeight() ) ) ) );
    }
}

void NOC_6_08_SeparationAndSeekApp::mouseDown( MouseEvent event )
{
}

void NOC_6_08_SeparationAndSeekApp::mouseMove( MouseEvent event ) {
    mMousePos = event.getPos();
}

void NOC_6_08_SeparationAndSeekApp::mouseDrag( MouseEvent event ) {
    mVehicles.push_back( new Vehicle ( event.getPos() ) );
}


void NOC_6_08_SeparationAndSeekApp::update()
{
    for (auto v : mVehicles ) {
        v->update();
        v->applyBehaviors( mVehicles, mMousePos );
    }
    
}

void NOC_6_08_SeparationAndSeekApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    for ( auto v : mVehicles ) {
        v->draw();
    }
}

CINDER_APP_NATIVE( NOC_6_08_SeparationAndSeekApp, RendererGl )
