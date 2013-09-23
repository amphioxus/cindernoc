// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 2-06: Attraction


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"
#include "Attractor.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_2_6_attractionApp : public AppNative {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void mouseUp( MouseEvent event );
    void keyDown ( KeyEvent event );
	void update();
	void draw();
    
    std::list<Attractor *> mAttractors;
    std::list<Mover *> mMovers;
    ci::Vec2f mousepos;
    
};

void NOC_2_6_attractionApp::prepareSettings(Settings *settings) {
    settings->setWindowSize(800, 600);
}
void NOC_2_6_attractionApp::setup()
{
    // create two attractors:
    mAttractors.push_back( new Attractor() );
    mAttractors.push_back( new Attractor( ci::Vec2f (100., 100.), 30) );

    // create one mover:
    mMovers.push_back( new Mover() );
}

void NOC_2_6_attractionApp::mouseDown( MouseEvent event )
{
    for (auto a : mAttractors) {
        a->clicked(mousepos);
    }    
}

void NOC_2_6_attractionApp::mouseMove( MouseEvent event )
{
    mousepos = event.getPos();
}

void NOC_2_6_attractionApp::mouseDrag( MouseEvent event ) {
    mouseMove( event );
    for (auto a : mAttractors) {
        a->dragged( mousepos );
    }
}

void NOC_2_6_attractionApp::mouseUp( MouseEvent event ) {
    for (auto a : mAttractors) {
        a->mouseup();
    }
}

void NOC_2_6_attractionApp::keyDown(KeyEvent event ) {
    if ( event.getChar() == 'f' ) {
        // Toggle between full-screen and window:
        setFullScreen( ! isFullScreen() );
    }
    else if (event.getChar() == 'a' ) {
        mMovers.push_back( new Mover() );
    }
    else if (event.getChar() == 'd' ) {
        mMovers.pop_front();
    }
    else if (event.getChar() == 'x' ) {
        mMovers.clear();
    }
}

void NOC_2_6_attractionApp::update()
{
    // go through attractors
    for (auto a : mAttractors) {
        a->hover(mousepos);
        // go through all movers for each attractor
        for (auto m : mMovers) {
            ci::Vec2f force = a->attract(m);
            m->apply_force( force );
        }        
    }  
}


void NOC_2_6_attractionApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    // Iterate through attractors
    for (auto a : mAttractors) {
        a->display();
    }
    
    for (auto m : mMovers) {
        m->update();
        m->display();
        m->display_history();
    }
}

CINDER_APP_NATIVE( NOC_2_6_attractionApp, RendererGl )
