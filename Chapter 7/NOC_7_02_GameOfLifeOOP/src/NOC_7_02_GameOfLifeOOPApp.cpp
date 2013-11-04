/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 7-2: Game of Life
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "GOL.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_7_02_GameOfLifeOOPApp : public AppNative {
  public:
    GOL *gol;
	void setup();
	void mouseDown( MouseEvent event );
    void resize();
	void update();
	void draw();
};

void NOC_7_02_GameOfLifeOOPApp::setup()
{
    gol = new GOL();
}

void NOC_7_02_GameOfLifeOOPApp::mouseDown( MouseEvent event )
{
    if (event.isRightDown()) {
        gol->reset();
    }
    else if (event.isLeftDown()) {
        gol->giveBirth( event.getPos() );
    }
    
}

void NOC_7_02_GameOfLifeOOPApp::resize() {
    gol->resize();
}

void NOC_7_02_GameOfLifeOOPApp::update()
{
    gol->generate();
}

void NOC_7_02_GameOfLifeOOPApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    gol->draw();
}

CINDER_APP_NATIVE( NOC_7_02_GameOfLifeOOPApp, RendererGl )
