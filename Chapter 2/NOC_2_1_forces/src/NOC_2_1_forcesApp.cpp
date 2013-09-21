// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 2-01: Setting up forces


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_2_1_forcesApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
    void mouseMove( MouseEvent event );
    void mouseDrag (MouseEvent event );
	void update();
	void draw();
    
    std::vector<Mover *> movers; // C++ vector to store pointers to Mover objects
    ci::Vec2f mouse; // store mouse position
    
};

void NOC_2_1_forcesApp::setup()
{
        movers.push_back( new Mover() );
}

void NOC_2_1_forcesApp::mouseDown( MouseEvent event )
{
}

void NOC_2_1_forcesApp::mouseMove( MouseEvent event )
{
    mouse = event.getPos();
}

void NOC_2_1_forcesApp::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}


void NOC_2_1_forcesApp::update()
{
    ci::Vec2f wind (0.01, 0);
    ci::Vec2f gravity (0, 0.1);
    
    for (auto m : movers) {
        m->apply_force(wind);
        m->apply_force(gravity);
        m->update();
    }
}


void NOC_2_1_forcesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    // iterate through all the Movers in the list:
    for (auto m : movers) {
        m->display_history();
        m->display();
        m->checkEdges();
    }
}

CINDER_APP_NATIVE( NOC_2_1_forcesApp, RendererGl )
