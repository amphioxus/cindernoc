#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_2_2_forces_many : public AppNative {
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

void NOC_2_2_forces_many::setup()
{
    ci::Rand::randomize();
    for (int i = 0; i < 20; i++) {
        movers.push_back( Mover( ci::Rand::randFloat(0.1f, 4.f), 0, 0 ) );        
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
    ci::Vec2f wind (0.01, 0);
    ci::Vec2f gravity (0, 0.1);
    for ( std::list<Mover>::iterator it = movers.begin(); it != movers.end(); it++)
    {
        it->apply_force(wind);
        it->apply_force(gravity);
        it->update();
    }
}


void NOC_2_2_forces_many::draw()
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

CINDER_APP_NATIVE( NOC_2_2_forces_many, RendererGl )
