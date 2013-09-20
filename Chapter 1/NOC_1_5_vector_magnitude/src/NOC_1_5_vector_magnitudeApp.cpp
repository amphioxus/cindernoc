// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 1-5: Vector magnitude

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 200;

class NOC_1_5_vector_magnitudeApp : public AppNative {
  public:
	void setup();
    void prepareSettings( Settings *settings );
    void mouseMove( MouseEvent event );
    void mouseDrag (MouseEvent event );
	void update();
	void draw();
private:
    ci::Vec2f mouse;
};

void NOC_1_5_vector_magnitudeApp::setup()
{
}

void NOC_1_5_vector_magnitudeApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
}

void NOC_1_5_vector_magnitudeApp::mouseMove( MouseEvent event )
{
    mouse = event.getPos();
}

void NOC_1_5_vector_magnitudeApp::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}

void NOC_1_5_vector_magnitudeApp::update()
{
}

void NOC_1_5_vector_magnitudeApp::draw()
{
    // create vector with window center coordinates:
    Vec2f center (getWindowWidth()/2. , getWindowHeight()/2. );
    
    // subtract center from mouse position vector
    Vec2f c2mouse = mouse - center;
    // calculate magnitude (length) of center->mouse vector    
    float m = c2mouse.length();
    
    // create rectangle class to display vector length as bar
    // First two variables are upper left corners, second two
    // are lower right corners of rectangle:
    Rectf rect (0., 0., m, 10.);
    
    // Let's start drawing:
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::color( 1.0f, 0.5f, 0.25f );
    gl::lineWidth(3.0);
    // Draw the line from center to mouse:
    gl::drawLine(center, mouse);
    // Draw the rectangle representing vector length
    gl::drawSolidRect(rect);
    
}

CINDER_APP_NATIVE( NOC_1_5_vector_magnitudeApp, RendererGl )
