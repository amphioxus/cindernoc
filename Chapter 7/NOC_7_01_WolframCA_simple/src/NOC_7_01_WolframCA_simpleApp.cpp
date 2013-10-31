/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 7-1: Wolfram Cellular Automata (Simple)
 
 */

#include "cinder/app/AppNative.h"
#include "CA.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_7_01_WolframCA_simpleApp : public AppNative {
    CA * ca;
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void resize();
	void update();
	void draw();
};


void NOC_7_01_WolframCA_simpleApp::setup()
{
    ca = new CA();
}


void NOC_7_01_WolframCA_simpleApp::mouseDown( MouseEvent event )
{
}

void NOC_7_01_WolframCA_simpleApp::resize() {
    ca->init();
}


void NOC_7_01_WolframCA_simpleApp::update()
{
    if (ca->mGeneration < ca->mVcells-1 ) {
        ca->generate();
    }
}


void NOC_7_01_WolframCA_simpleApp::draw()
{
  
    // clear out the window with black
    gl::clear( Color( 0, 0, 0 ) );
    
    ca->draw();
}

CINDER_APP_NATIVE( NOC_7_01_WolframCA_simpleApp, RendererGl )
