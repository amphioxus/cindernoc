// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)

// Example 3-4: Polar To Cartesian
//
//  Convert a polar coordinate (r,theta) to cartesian (x,y):
//  x = r * cos(theta)
//  y = r * sin(theta)
// 

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_3_04_PolarToCartesianApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    float r, theta, x, y;
};

void NOC_3_04_PolarToCartesianApp::setup()
{
    // initialize values
    r = getWindowHeight() * 0.45;
    theta = 0;
}

void NOC_3_04_PolarToCartesianApp::mouseDown( MouseEvent event )
{
}

void NOC_3_04_PolarToCartesianApp::update()
{
}

void NOC_3_04_PolarToCartesianApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::pushMatrices();
    gl::translate( ci::Vec2f (getWindowWidth()/2, getWindowHeight()/2));
    
    // convert polar to cartesian:
    
    x = r * cos(theta);
    y = r * sin(theta);
    
    gl::color(0.68, 0.68, 0.68, 0.4);
    gl::drawSolidCircle(ci::Vec2f (x, y), 30.0);
    gl::drawLine(ci::Vec2f(0.,0.), ci::Vec2f (x, y));
    gl::popMatrices();
    
    // Increase the angle over time
    theta += 0.02;
    
    
}

CINDER_APP_NATIVE( NOC_3_04_PolarToCartesianApp, RendererGl )
