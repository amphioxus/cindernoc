// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 5-1: Box2D Exercise (Boxes without Box2D integration)

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Box.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_5_1_box2d_exerciseApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    std::vector<Box *> mBoxes;
};

void NOC_5_1_box2d_exerciseApp::setup()
{
}

void NOC_5_1_box2d_exerciseApp::mouseDown( MouseEvent event )
{
    mBoxes.push_back( new Box( event.getPos() ) );
}

void NOC_5_1_box2d_exerciseApp::update()
{
}

void NOC_5_1_box2d_exerciseApp::draw()
{
	// clear out the window with white
	gl::clear( Color( 1, 1, 1 ) );
    
    for (auto box : mBoxes) {
        box->draw();
    }
    
}

CINDER_APP_NATIVE( NOC_5_1_box2d_exerciseApp, RendererGl )
