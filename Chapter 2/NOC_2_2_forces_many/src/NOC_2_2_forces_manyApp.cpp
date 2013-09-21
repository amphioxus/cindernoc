// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 2-02: Multiple forces (eg. wind, gravity)

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_2_2_forces_many : public AppNative {
    
private:
    ci::Vec2f wind = ci::Vec2f (0.01, 0);
    ci::Vec2f gravity = ci::Vec2f  (0, 0.1);
    
public:
	void setup();
	void mouseDown( MouseEvent event );	
    void mouseMove( MouseEvent event );
    void mouseDrag (MouseEvent event );
	void update();
	void draw();
    
    std::vector<Mover *> mMovers; // C++ list to store Mover objects
    ci::Vec2f mouse; // store mouse position
};


void NOC_2_2_forces_many::setup()
{
    ci::Rand::randomize();
    for (int i = 0; i < 20; i++) {
        mMovers.push_back( new Mover( ci::Rand::randFloat(0.1f, 4.f), 0, 0 ) );
    }
        
}

void NOC_2_2_forces_many::mouseDown( MouseEvent event )
{
}

void NOC_2_2_forces_many::mouseMove( MouseEvent event )
{
    mouse = event.getPos();
}

void NOC_2_2_forces_many::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}


void NOC_2_2_forces_many::update()
{    
    for (auto mover : mMovers) {
        mover->apply_force( wind );
        mover->apply_force( gravity );
        mover->update();
    }
}


void NOC_2_2_forces_many::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    // iterate through all the Movers in the list:
    for (auto mover : mMovers) {
        mover->display_history();
        mover->display();
        mover->checkEdges();
    }    
}

CINDER_APP_NATIVE( NOC_2_2_forces_many, RendererGl )
