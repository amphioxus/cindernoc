// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 4-3: Particle System class

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ParticleSystem.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_4_03_ParticleSystemClassApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    std::vector<ParticleSystem *> mParticleSystems; // vector of Particle System
};

void NOC_4_03_ParticleSystemClassApp::setup()
{
    setFrameRate(30.);
    mParticleSystems.push_back( new ParticleSystem( ci::Vec2f (getWindowWidth()/2, 50) ) ) ;
}

void NOC_4_03_ParticleSystemClassApp::mouseDown( MouseEvent event )
{
    mParticleSystems.push_back( new ParticleSystem( event.getPos() ));
}

void NOC_4_03_ParticleSystemClassApp::update()
{
    for (auto ps : mParticleSystems ) {
        ps->update();
    }
}

void NOC_4_03_ParticleSystemClassApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    for (auto ps : mParticleSystems ) {
        ps->draw();
    }
}

CINDER_APP_NATIVE( NOC_4_03_ParticleSystemClassApp, RendererGl )
