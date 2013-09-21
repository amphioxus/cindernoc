// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)

// Example 1-2: Bouncing Ball, with Cinder Vector!

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 200;

class NOC_1_2_bouncingball_vectorsApp : public AppNative {
  public:
	void setup();
    void prepareSettings( Settings *settings );
	void draw();
    
private:
    float radius = 32;
    ci::Vec2f location;
    ci::Vec2f velocity;
    
};

void NOC_1_2_bouncingball_vectorsApp::setup()
{
    setFrameRate(60.);
    // set location and velocity:
    location = ci::Vec2f (100, 100);
    velocity = ci::Vec2f (2.5, 2.0);
    // alternatively:
//    location.x = 100; location.y = 100;
//    velocity.x = 2.5; velocity.y = 2.;
}

void NOC_1_2_bouncingball_vectorsApp::prepareSettings(Settings *settings) {
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
}


void NOC_1_2_bouncingball_vectorsApp::draw()
{
	// clear out the window with white
	gl::clear( Color( 1, 1, 1 ) );
    
    // Add the current speed to the location.
    location += velocity;
    
    if ((location.x > getWindowWidth() ) || (location.x < 0)) {
        velocity.x = velocity.x * -1;
    }
    if ((location.y > getWindowHeight() ) || (location.y < 0)) {
        velocity.y = velocity.y * -1;
    }
    
    gl::color(.6, .6, .6);
    gl::drawSolidCircle( location, radius );
    gl::color(0, 0, 0);
    gl::lineWidth(3.);
    gl::drawStrokedCircle( location, radius );
    
}

CINDER_APP_NATIVE( NOC_1_2_bouncingball_vectorsApp, RendererGl )
