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
    
    std::list<Mover> movers; // C++ list to store Mover objects
    ci::Vec2f mouse; // store mouse position
    
};

void NOC_2_4_forces_friction::setup()
{
//    setFrameRate(2.f);
    ci::Rand::randomize();
    for (int i = 0; i < 4; i++) {
        movers.push_back( Mover( ci::Rand::randFloat(1.f, 4.f), ci::Rand::randFloat( ci::app::getWindowWidth() ), 0 ) );
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
    
    for ( std::list<Mover>::iterator it = movers.begin(); it != movers.end(); it++)
    {
        
        // Gravity: normalized by mass
        ci::Vec2f gravity (0, 0.1 * it->mass );
        
        // Friction:
        ci::Vec2f friction;
        friction = it->velocity.safeNormalized(); // SAFE normalize is the key!
        friction = friction * -1 * cf; // reverse the force
//        std::cout << friction << std::endl;
        
        it->apply_force(friction); // comment this to turn off friction
        
        it->apply_force(wind);
        it->apply_force(gravity);
        
        it->update();
    }
}


void NOC_2_4_forces_friction::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    // iterate through all the Movers in the list:
    for ( std::list<Mover>::iterator it = movers.begin(); it != movers.end(); it++)
    {
        
        it->display_history();
        it->display();
        it->checkEdges();
    }
    
}

CINDER_APP_NATIVE( NOC_2_4_forces_friction, RendererGl )
