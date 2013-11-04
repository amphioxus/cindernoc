/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 8-2: Simple Recursion
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_8_02_RecursionApp : public AppNative {
  public:
    bool alreadyDrawn = false;
	void setup();
    void prepareSettings( Settings * settings);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    void drawCircle( float x, float y, float r );
    
};

void NOC_8_02_RecursionApp::setup()
{
    setFrameRate(5); // quick-fix to prevent recursion from happening at 60Hz
}

void NOC_8_02_RecursionApp::prepareSettings( Settings *settings) {
    settings->setWindowSize(800, 200);
    settings->setResizable( false );
}

void NOC_8_02_RecursionApp::mouseDown( MouseEvent event )
{
}

void NOC_8_02_RecursionApp::update()
{
}

void NOC_8_02_RecursionApp::draw()
{
    if (alreadyDrawn == false ) {
        // clear out the window with black
        gl::clear( Color( 0, 0, 0 ) );
        gl::color(1, 0, 0);
        drawCircle(getWindowWidth()/2, getWindowHeight()/2, 400);
        alreadyDrawn = true;
    }
}


void NOC_8_02_RecursionApp::drawCircle(float x, float y, float r) {
    
    ci::Vec2f loc = ci::Vec2f(x, y);
    gl::drawStrokedCircle(loc, r);
    
    if (r > 2) {
      // Now we draw two more circles, one to the left
      // and one to the right
        drawCircle(x + r/2, y, r/2);
        drawCircle(x - r/2, y, r/2);
    }
}

CINDER_APP_NATIVE( NOC_8_02_RecursionApp, RendererGl )
