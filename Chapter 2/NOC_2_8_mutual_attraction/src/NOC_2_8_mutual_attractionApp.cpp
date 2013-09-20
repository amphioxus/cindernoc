#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_2_8_mutual_attractionApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    std::list<Mover> movers; // TODO: needs to be changed to pointer
};

void NOC_2_8_mutual_attractionApp::setup()
{
    setFullScreen(TRUE);
    setFrameRate(30.f);
    for (int i = 0; i < 20; i++) {
        movers.push_back( Mover() );
    }
}  

void NOC_2_8_mutual_attractionApp::mouseDown( MouseEvent event )
{
}

void NOC_2_8_mutual_attractionApp::keyDown(KeyEvent event) {
    if ( event.getChar() == 'f' ) {
        // Toggle between full-screen and window:
        setFullScreen( ! isFullScreen() );
    }
}

void NOC_2_8_mutual_attractionApp::update()
{
    for (std::list<Mover>::iterator it = movers.begin(); it != movers.end(); it++) {        
        for (std::list<Mover>::iterator itinner = movers.begin(); itinner != movers.end(); itinner++) {
            if ( it != itinner ) {
                ci::Vec2f force = itinner->attract( *it );
                it->apply_force( force );
                it->update();
            }
        }        
    }
}

void NOC_2_8_mutual_attractionApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    for (std::list<Mover>::iterator it = movers.begin(); it != movers.end(); it++) {
        it->display();
    }
}

CINDER_APP_NATIVE( NOC_2_8_mutual_attractionApp, RendererGl )
