// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
// 
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)

// Example 1-1: Bouncing Ball, no vectors


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 200;

class NOC_1_1_bouncingball_novectorsApp : public AppNative {
  public:
	void setup();
    void prepareSettings( Settings *settings );
	void draw();

private:
    float radius = 32;
    float x = 100;
    float y = 100;
    float xspeed = 2.5;
    float yspeed = 2;
        
};

void NOC_1_1_bouncingball_novectorsApp::prepareSettings(Settings *settings) {
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
}

void NOC_1_1_bouncingball_novectorsApp::setup()
{
    setFrameRate(60.);
}

void NOC_1_1_bouncingball_novectorsApp::draw()
{
	// clear out the window with white
	gl::clear( Color( 1, 1, 1 ) );
    
    // Add the current speed to the location.
    x = x + xspeed;
    y = y + yspeed;
    
    if ((x > getWindowWidth() ) || (x < 0)) {
        xspeed = xspeed * -1;
    }
    if ((y > getWindowHeight() ) || (y < 0)) {
        yspeed = yspeed * -1;
    }
    
    // I actually don't know how to easily draw circles WITHOUT using vectors
    // so I'm cheating:
    ci::Vec2f center;
    center.x = x;
    center.y = y;

    gl::color(.6, .6, .6);
    gl::drawSolidCircle( center, radius );
    gl::color(0, 0, 0);
    gl::lineWidth(3.);
    gl::drawStrokedCircle( center, radius );
    
    
}

CINDER_APP_NATIVE( NOC_1_1_bouncingball_novectorsApp, RendererGl )
