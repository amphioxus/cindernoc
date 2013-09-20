// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 1-6: Demonstration of normalizing a vector.
// Normalizing a vector sets its length to 1.

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 200;

class NOC_1_6_vector_normalizeApp : public AppNative {
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

void NOC_1_6_vector_normalizeApp::setup()
{
}

void NOC_1_6_vector_normalizeApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
}

void NOC_1_6_vector_normalizeApp::mouseMove( MouseEvent event )
{
    mouse = event.getPos();
}

void NOC_1_6_vector_normalizeApp::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}

void NOC_1_6_vector_normalizeApp::update()
{
}

void NOC_1_6_vector_normalizeApp::draw()
{
    // create vector with window center coordinates:
    Vec2f center (getWindowWidth()/2. , getWindowHeight()/2. );
    
    // subtract center from mouse position vector
    Vec2f c2mouse = mouse - center;
    c2mouse.normalize(); // Normalize vector
    c2mouse *= 50; // multiply by 50 to make it more visible
    c2mouse += center; // add normal vector back to the window center vector
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::color( 1.0f, 0.5f, 0.25f );
    gl::lineWidth(3.0);
    // Draw the line from center to mouse:
    gl::drawLine(center, c2mouse);
}

CINDER_APP_NATIVE( NOC_1_6_vector_normalizeApp, RendererGl )
