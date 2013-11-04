/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 8-1: Simple Recursion
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_8_01_RecursionApp : public AppNative {
  public:
    bool alreadyDrawn = false;
	void setup();
	void mouseDown( MouseEvent event );
    void resize();
	void update();
	void draw();
    
    void drawCircle( ci::Vec2f c, float r );
};

void NOC_8_01_RecursionApp::setup()
{
    setFrameRate(5); // quick-fix to prevent recursion from happening at 60Hz
}

void NOC_8_01_RecursionApp::mouseDown( MouseEvent event )
{
    alreadyDrawn = false;

}
void NOC_8_01_RecursionApp::resize() {
    alreadyDrawn = false;
}

void NOC_8_01_RecursionApp::update()
{
}

void NOC_8_01_RecursionApp::draw()
{
    if (alreadyDrawn == false) {
        // clear out the window with black
        gl::clear( Color( 0, 0, 0 ) );
        gl::color(1, 0, 0);
        drawCircle( ci::Vec2f(getWindowWidth()/2,
                              getWindowHeight()/2),
                   getWindowWidth()/2 );
        alreadyDrawn = true;
    }

}


void NOC_8_01_RecursionApp::drawCircle(ci::Vec2f c, float r) {
    
    gl::drawStrokedCircle(c, r);
    
    if (r > 2) {
        r *= 0.75f;
        drawCircle(c, r);
    }
    
}



CINDER_APP_NATIVE( NOC_8_01_RecursionApp, RendererGl )
