// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 2-04: Friction

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_2_4_forces_friction : public AppNative {
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

void NOC_2_4_forces_friction::setup()
{
//    setFrameRate(2.f);
    ci::Rand::randomize();
    for (int i = 0; i < 4; i++) {
        mMovers.push_back( new Mover( ci::Rand::randFloat(1.f, 4.f), ci::Rand::randFloat( ci::app::getWindowWidth() ), 0 ) );
    }
        
}

void NOC_2_4_forces_friction::mouseDown( MouseEvent event )
{
}

void NOC_2_4_forces_friction::mouseMove( MouseEvent event )
{
    mouse = event.getPos();
}

void NOC_2_4_forces_friction::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}


void NOC_2_4_forces_friction::update()
{
    ci::Vec2f wind (0.01, 0);
    float cf = 0.05; // friction coefficient
    for (auto m : mMovers) {
        // Gravity: normalized by mass
        ci::Vec2f gravity (0, 0.1 * m->mass );
        
        // Friction:
        ci::Vec2f friction;
        friction = m->velocity.safeNormalized(); // SAFE normalize is the key!
        friction = friction * -1 * cf; // reverse the force
        
        m->apply_force( friction ); // comment this to turn off friction
        
        m->apply_force( wind );
        m->apply_force( gravity );
        
        m->update();        
    }
}


void NOC_2_4_forces_friction::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    // iterate through all the Movers in the list:
    for (auto m : mMovers) {
        m->display_history();
        m->display();
        m->checkEdges();
    }
}

CINDER_APP_NATIVE( NOC_2_4_forces_friction, RendererGl )
