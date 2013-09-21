// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 2-03: "Real" gravity

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_2_3_forces_many_realgravity : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
    void mouseMove( MouseEvent event );
    void mouseDrag (MouseEvent event );
	void update();
	void draw();
    
    std::vector<Mover *> movers; // C++ vector to store Mover objects
    ci::Vec2f mouse; // store mouse position
    
};

void NOC_2_3_forces_many_realgravity::setup()
{
    ci::Rand::randomize();
    for (int i = 0; i < 20; i++) {
        movers.push_back( new Mover( ci::Rand::randFloat(0.1f, 4.f), 0, 0 ) );
    }
        
}

void NOC_2_3_forces_many_realgravity::mouseDown( MouseEvent event )
{
}

void NOC_2_3_forces_many_realgravity::mouseMove( MouseEvent event )
{
    mouse = event.getPos();
}

void NOC_2_3_forces_many_realgravity::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}


void NOC_2_3_forces_many_realgravity::update()
{
    ci::Vec2f wind (0.01, 0);
    
    for (auto m : movers) {
        ci::Vec2f gravity (0, 0.1 * m->mass );
        m->apply_force( wind );
        m->apply_force( gravity );
        m->update();
    }
}


void NOC_2_3_forces_many_realgravity::draw()
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

CINDER_APP_NATIVE( NOC_2_3_forces_many_realgravity, RendererGl )
