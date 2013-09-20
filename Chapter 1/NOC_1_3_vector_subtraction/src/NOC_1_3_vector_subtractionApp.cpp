// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)

// Example 1-3: Vector subtraction
// I didn't translate this example, because in order to achieve the effect
// one doesn't really need to subtract a vector.  In Processing,
//       line(width/2,height/2,mouse.x,mouse.y);
// without prior subtraction step would have sufficed to show a line from the
// window center to the cursor position. Since I don't know how to translate
// Processing's "translate()" function, I did the same here in Cinder.
// However, subtracting ci::vectors is easy. Just use the "-" (minus) sign.
// See the next example (1.4) for actual vector subtraction.

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
    
    // clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::color( 1.0f, 0.5f, 0.25f );
    gl::lineWidth(3.0);
    
    // This is easier (no vector subtraction necessary:
    gl::drawLine(center, mouse);
    
    // But ci::vectors can be subtracted just like this:
    // v3 = v2 - v1;
    
}

CINDER_APP_NATIVE( NOC_1_3_vector_subtractionApp, RendererGl )
