// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)


// Example 1-4: Vector multiplication

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 200;

class NOC_1_4_vector_multiplicationApp : public AppNative {
  public:
    void prepareSettings( Settings *settings );
	void mouseMove( MouseEvent event );
    void mouseDrag (MouseEvent event );
	void draw();
private:
    ci::Vec2f mouse;
};



void NOC_1_4_vector_multiplicationApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
}


void NOC_1_4_vector_multiplicationApp::mouseMove( MouseEvent event )
{
    mouse = event.getPos();
}

void NOC_1_4_vector_multiplicationApp::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}

void NOC_1_4_vector_multiplicationApp::draw()
{
    // create vector with window center coordinates:
    Vec2f center (getWindowWidth()/2. , getWindowHeight()/2. );
    
    // subtract center from mouse position vector
    Vec2f c2mouse = mouse - center;
    c2mouse *= 0.5; // vector multiplication to produce vector of half the length
    c2mouse += center; // add the halfling back to the window center vector
    
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    gl::color( 1.0f, 0.5f, 0.25f );
    gl::lineWidth(3.0);
    
    gl::drawLine(center, c2mouse);
    

}

CINDER_APP_NATIVE( NOC_1_4_vector_multiplicationApp, RendererGl )
