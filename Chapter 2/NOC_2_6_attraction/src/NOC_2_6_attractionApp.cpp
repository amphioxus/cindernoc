// Implementation using a std::list

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
    
    std::list<Attractor> attractors;
    std::list<Mover> movers;
    ci::Vec2f mousepos;
    
};

void NOC_2_6_attractionApp::prepareSettings(Settings *settings) {
    settings->setWindowSize(800, 600);
}
void NOC_2_6_attractionApp::setup()
{
    // create two attractors:
    attractors.push_back( Attractor() );
    attractors.push_back( Attractor( ci::Vec2f (100., 100.), 30) );

    // create one mover:
    movers.push_back( Mover() );
}

void NOC_2_6_attractionApp::mouseDown( MouseEvent event )
{
    for (std::list<Attractor>::iterator it = attractors.begin(); it != attractors.end(); it++) {
        it->clicked(mousepos);
    }
    
}

void NOC_2_6_attractionApp::mouseMove( MouseEvent event )
{
    mousepos = event.getPos();
}

void NOC_2_6_attractionApp::mouseDrag( MouseEvent event ) {
    mouseMove( event );
    for (std::list<Attractor>::iterator it = attractors.begin(); it != attractors.end(); it++) {
        it->dragged(mousepos);
    }
}

void NOC_2_6_attractionApp::mouseUp( MouseEvent event ) {
    for (std::list<Attractor>::iterator it = attractors.begin(); it != attractors.end(); it++) {
        it->mouseup();
    }
}

void NOC_2_6_attractionApp::keyDown(KeyEvent event ) {
    if ( event.getChar() == 'f' ) {
        // Toggle between full-screen and window:
        setFullScreen( ! isFullScreen() );
    }
    else if (event.getChar() == 'a' ) {
        movers.push_back( Mover() );
    }
    else if (event.getChar() == 'd' ) {
        movers.pop_front();
    }
    else if (event.getChar() == 'x' ) {
        movers.clear();
    }
}

void NOC_2_6_attractionApp::update()
{
    // go through attractors
    for (std::list<Attractor>::iterator it = attractors.begin(); it != attractors.end(); it++) {
        it->hover(mousepos);
        
        // go through movers for each attractor
        for (std::list<Mover>::iterator mit = movers.begin(); mit != movers.end(); mit++) {
            ci::Vec2f force = it->attract( *mit );
            mit->apply_force(force);
        }
    }   
}

void NOC_2_6_attractionApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    // Iterate through attractors
    for (std::list<Attractor>::iterator it = attractors.begin(); it != attractors.end(); it++) {
        it->display();
    }
    
    for (std::list<Mover>::iterator mit = movers.begin(); mit != movers.end(); mit++) {
        mit->update();
        mit->display();
        mit->display_history();
    }
}

CINDER_APP_NATIVE( NOC_2_6_attractionApp, RendererGl )
