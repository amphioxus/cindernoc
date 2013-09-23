// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 4-7: Particle Systems with Repeller object


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ParticleSystem.h"
#include "Repeller.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_4_07_ParticleSystemForcesRepellerApp : public AppNative {
    
    ci::Vec2f mGravityForce = ci::Vec2f (0,0.1);
  public:
	void setup();
	void mouseDown( MouseEvent event );
	void mouseMove( MouseEvent event );
    void keyDown (KeyEvent event);
	void update();
	void draw();
    
    std::vector< ParticleSystem * > mParticleSystems; // vector of Particle Systems
    Repeller * repeller;  // Repeller object
    
};

void NOC_4_07_ParticleSystemForcesRepellerApp::setup()
{
    setFrameRate(30.);
    mParticleSystems.push_back( new ParticleSystem( ci::Vec2f (getWindowWidth()/2, 150 ) ) ) ;
    repeller = new Repeller( ci::Vec2f (getWindowWidth()/2 - 20, getWindowHeight()/2 ));
}

void NOC_4_07_ParticleSystemForcesRepellerApp::mouseDown( MouseEvent event ) {
    mParticleSystems.push_back( new ParticleSystem( event.getPos() ));
}

void NOC_4_07_ParticleSystemForcesRepellerApp::mouseMove( MouseEvent event ) {
    
}

void NOC_4_07_ParticleSystemForcesRepellerApp::keyDown( KeyEvent event) {
    if ( event.getChar() == 'f' ) {
        // Toggle between full-screen and window:
        setFullScreen( ! isFullScreen() );
    } else if ( event.getChar() == 'x') {
        mParticleSystems.clear();
    }
}

void NOC_4_07_ParticleSystemForcesRepellerApp::update()
{
    for (auto ps : mParticleSystems ) {
        ps->applyRepeller( repeller );
        ps->applyForce( mGravityForce );
        ps->update();
    }
}

void NOC_4_07_ParticleSystemForcesRepellerApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    repeller->draw();
    
    for (auto ps : mParticleSystems ) {
        ps->draw();
    }
    
    
}

CINDER_APP_NATIVE( NOC_4_07_ParticleSystemForcesRepellerApp, RendererGl )
