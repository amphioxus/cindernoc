// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 2-08: Mutual attraction

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
    void resetMovers();
    
    std::list<Mover *> mMovers;
    bool displayHistory = FALSE;
};

void NOC_2_8_mutual_attractionApp::setup()
{
    setFullScreen(FALSE);
    setFrameRate(30.f);
    resetMovers();
}  

void NOC_2_8_mutual_attractionApp::mouseDown( MouseEvent event )
{
}

void NOC_2_8_mutual_attractionApp::keyDown(KeyEvent event) {
    if ( event.getChar() == 'f' ) {
        // Toggle between full-screen and window:
        setFullScreen( ! isFullScreen() );
    } else if ( event.getChar() == 'h' ) {
        // Toggle between drawing history trails or not:
        displayHistory = !displayHistory ;
    } else if (event.getChar() == 'x') {
        resetMovers();
    }    
}


void NOC_2_8_mutual_attractionApp::update()
{
    // double loop: each mover needs to calculate attraction to all other movers, excluding itself
    for (auto mo : mMovers) {
        for (auto mi : mMovers) {            
            if (mi != mo) {
                ci::Vec2f force = mi->attract( mo );
                mi->apply_force( force );
                mi->update();
            }
        }
    }
}


void NOC_2_8_mutual_attractionApp::resetMovers(){
    if (!mMovers.empty())
        mMovers.clear();
        
    for (int i = 0; i < 20; i++) {
        mMovers.push_back( new Mover() );
    }
}


void NOC_2_8_mutual_attractionApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    for (auto m : mMovers) {
        m->display();
        if (displayHistory)
            m->display_history();
    }

}

CINDER_APP_NATIVE( NOC_2_8_mutual_attractionApp, RendererGl )
