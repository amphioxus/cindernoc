/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 8-5: Koch Fractal
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "KochFractal.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_8_05_KochApp : public AppNative {
  public:
    KochFractal * koch;
	void setup();
    void prepareSettings( Settings * settings );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void NOC_8_05_KochApp::setup()
{
    koch = new KochFractal();
}

void NOC_8_05_KochApp::prepareSettings( Settings * settings ) {
    settings->setWindowSize(800, 400);
}


void NOC_8_05_KochApp::mouseDown( MouseEvent event )
{
    if (event.isRightDown() ) {
        koch->restart();
    }
    else if ( koch->getCount() < 6) {
        koch->nextLevel();
    }
}


void NOC_8_05_KochApp::update()
{
}

void NOC_8_05_KochApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    koch->draw();
}

CINDER_APP_NATIVE( NOC_8_05_KochApp, RendererGl )
