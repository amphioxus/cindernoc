#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Exercise_8_01_RecursionLinesApp : public AppNative {
  public:
    ci::Vec2f P1, P2; // start and end location of lines
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void Exercise_8_01_RecursionLinesApp::setup()
{
    
}

void Exercise_8_01_RecursionLinesApp::mouseDown( MouseEvent event )
{
}

void Exercise_8_01_RecursionLinesApp::update()
{
}

void Exercise_8_01_RecursionLinesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( Exercise_8_01_RecursionLinesApp, RendererGl )
