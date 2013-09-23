// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)

// Example 3-5: Simple Harmonic Motion

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_3_05_simple_harmonic_motionApp : public AppNative {
  public:
	void setup();
	void prepareSettings(Settings *settings);
    void mouseDown( MouseEvent event );
	void update();
	void draw();
    
    float period = 120;
    float amplitude = 300;
};

void NOC_3_05_simple_harmonic_motionApp::setup()
{    
}

void NOC_3_05_simple_harmonic_motionApp::prepareSettings( Settings *settings ) {
    settings->setWindowSize(800, 600);
    settings->setFrameRate(60.);
}

void NOC_3_05_simple_harmonic_motionApp::mouseDown( MouseEvent event )
{
}

void NOC_3_05_simple_harmonic_motionApp::update()
{
}

void NOC_3_05_simple_harmonic_motionApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0.2, 0.2, 0.2 ) );

    // Calculating horizontal location according to formula for simple harmonic motion
    float x = amplitude * cos( 2 * M_PI *getElapsedFrames() / period);
    gl::pushMatrices();
    gl::translate( ci::Vec2f (getWindowWidth()/2, getWindowHeight()/2));
    ci::gl::color( ci::ColorA(.8f, .6f, .6f, 0.6f) );
    gl::lineWidth(3.0);
    gl::drawLine( ci::Vec2f(0.,0.), ci::Vec2f(x, 0.));
    gl::color(.8, .8, .8);
    gl::drawSolidCircle(ci::Vec2f(x, 0.), 24.0);
    gl::popMatrices();
}

CINDER_APP_NATIVE( NOC_3_05_simple_harmonic_motionApp, RendererGl )
