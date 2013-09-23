// Not a very CPU efficient solution...

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"
#include "Attractor.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_02forces_attractrepel : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    std::vector<Mover *> mMovers;
    std::list<Attractor *> mAttractors;
};

void NOC_02forces_attractrepel::setup()
{
//    setFullScreen(TRUE);
    setFrameRate(30.f);
        attractors.push_back(  Attractor() ); // create attractor);
    
    // create movers:
    for (int i = 0; i < 20; i++) {
        movers.push_back( Mover() );
    }
}  

void NOC_02forces_attractrepel::mouseDown( MouseEvent event )
{
}

void NOC_02forces_attractrepel::keyDown(KeyEvent event) {
    if ( event.getChar() == 'f' ) {
        // Toggle between full-screen and window:
        setFullScreen( ! isFullScreen() );
    }
}

void NOC_02forces_attractrepel::update()
{
    // iterate through each attractor:
    for (std::list<Attractor>::iterator at = attractors.begin(); at != attractors.end(); at++) {
        
        // iterate through each mover:
        for (std::list<Mover>::iterator it = movers.begin(); it != movers.end(); it++) {
            // for each mover, go through other movers to calculate mutual mover attraction:
            for (std::list<Mover>::iterator itinner = movers.begin(); itinner != movers.end(); itinner++) {
                // only if not itself:
                if ( it != itinner ) {
                    ci::Vec2f rf = itinner->repel( *it );
                    it->apply_force( rf );
                }
            }
            
            // calculate force towards attractor:
            ci::Vec2f af = at->attract( *it ); // calculate attraction force to attractor
            it->apply_force( af );
            
            it->update();
        }        
    }
}

void NOC_02forces_attractrepel::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    ci::gl::enableAlphaBlending();
    for (std::list<Attractor>::iterator at = attractors.begin(); at != attractors.end(); at++) {
        at->display();
    }
    for (std::list<Mover>::iterator it = movers.begin(); it != movers.end(); it++) {
        it->display();
//        it->display_history();
    }
    
    std::cout << getFrameRate() << std::endl;
    

}

CINDER_APP_NATIVE( NOC_02forces_attractrepel, RendererGl )
