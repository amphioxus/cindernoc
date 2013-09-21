// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)

// Example 1-3: Vector subtraction
//
// Done this way just to keep in line with the book
//
//       line(width/2,height/2,mouse.x,mouse.y); // (Processing code)
// without prior subtraction step would have sufficed to show a line from the
// window center to the cursor position. 

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 200;

class NOC_1_3_vector_subtractionApp : public AppNative {
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

void NOC_1_3_vector_subtractionApp::setup()
{
}

void NOC_1_3_vector_subtractionApp::prepareSettings(Settings *settings) {
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
}


void NOC_1_3_vector_subtractionApp::mouseMove( MouseEvent event )
{
    mouse = event.getPos();
}

void NOC_1_3_vector_subtractionApp::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}

void NOC_1_3_vector_subtractionApp::update()
{
}

void NOC_1_3_vector_subtractionApp::draw()
{
    
    // create vector with window center coordinates:
    Vec2f center (getWindowWidth()/2. , getWindowHeight()/2. );
    // Subtracting vectors is easy:
    Vec2f m = mouse - center;
    // clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    gl::pushMatrices();
    gl::translate( Vec2f (getWindowWidth()/2 , getWindowHeight()/2) );
    gl::color( 1.0f, 0.5f, 0.25f );
    gl::lineWidth(3.0);
    
    gl::drawLine( ci::Vec2f(0,0), m);
    
    gl::popMatrices();
    
}

CINDER_APP_NATIVE( NOC_1_3_vector_subtractionApp, RendererGl )
