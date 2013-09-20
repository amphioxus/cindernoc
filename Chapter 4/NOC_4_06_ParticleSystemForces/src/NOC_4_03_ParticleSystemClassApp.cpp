#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ParticleSystem.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_4_06_ParticleSystemForcesApp : public AppNative {
    
    ci::Vec2f mGravityForce = ci::Vec2f (0,0.1);
  public:
	void setup();
	void mouseDown( MouseEvent event );
	void mouseMove( MouseEvent event );
    void keyDown (KeyEvent event);
	void update();
	void draw();
    
    std::vector<ParticleSystem *> mParticleSystems; // vector of Particle System
};

void NOC_4_06_ParticleSystemForcesApp::setup()
{
    setFrameRate(30.);
    mParticleSystems.push_back( new ParticleSystem( ci::Vec2f (getWindowWidth()/2, getWindowHeight()/2 ) ) ) ;
}

void NOC_4_06_ParticleSystemForcesApp::mouseDown( MouseEvent event ) {
    mParticleSystems.push_back( new ParticleSystem( event.getPos() ));
}

void NOC_4_06_ParticleSystemForcesApp::mouseMove( MouseEvent event ) {
    
    // gravity direction & magnitude depends on mouse position
    mGravityForce.x = lmap<float>( event.getX(), 0, getWindowWidth(), -1.0, 1.0);
    mGravityForce.y = lmap<float>( event.getY(), 0, getWindowHeight(), -1.0, 1.0);
}

void NOC_4_06_ParticleSystemForcesApp::keyDown( KeyEvent event) {
    if ( event.getChar() == 'f' ) {
        // Toggle between full-screen and window:
        setFullScreen( ! isFullScreen() );
    }
}

void NOC_4_06_ParticleSystemForcesApp::update()
{
    for (auto ps : mParticleSystems ) {
        ps->applyForce( mGravityForce );
        ps->update();
    }
}

void NOC_4_06_ParticleSystemForcesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    for (auto ps : mParticleSystems ) {
        ps->draw();
    }
}

CINDER_APP_NATIVE( NOC_4_06_ParticleSystemForcesApp, RendererGl )
