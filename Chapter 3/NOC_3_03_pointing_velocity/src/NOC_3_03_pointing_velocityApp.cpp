#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_3_03_pointing_velocityApp : public AppNative {
  public:
	void setup();
    void prepareSettings(Settings *settings);
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    ci::Vec2f mousePos;
private:
    MoverRef mMover; // pointer to mover
};

void NOC_3_03_pointing_velocityApp::setup()
{
    mMover = MoverRef( new Mover() );
}

void NOC_3_03_pointing_velocityApp::prepareSettings( Settings *settings ) {
    settings->setWindowSize(800, 600);
}

void NOC_3_03_pointing_velocityApp::mouseDown( MouseEvent event )
{
}

void NOC_3_03_pointing_velocityApp::mouseMove( MouseEvent event ) {
    mousePos = event.getPos();
}


void NOC_3_03_pointing_velocityApp::keyDown(KeyEvent event) {
    if ( event.getChar() == 'f' ) {
        // Toggle between full-screen and window:
        setFullScreen( ! isFullScreen() );
    }
}


void NOC_3_03_pointing_velocityApp::update()
{
    mMover->update( mousePos );
    mMover->checkEdges();
}

void NOC_3_03_pointing_velocityApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    mMover->draw();
    mMover->draw_history();
    
    
}

CINDER_APP_NATIVE( NOC_3_03_pointing_velocityApp, RendererGl )
