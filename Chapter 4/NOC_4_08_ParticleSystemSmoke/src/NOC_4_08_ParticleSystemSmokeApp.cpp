// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 4-8: Particle Systems Smoke (alpha blending of textures)

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "ParticleSystem.h"
#include "VectorArrow.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_4_08_ParticleSystemSmokeApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    std::vector< ParticleSystem * > mParticleSystems; // vector of Particle Systems
    ci::Vec2f mGravityForce = ci::Vec2f (0,-0.05);
    ci::Vec2f mMousePos;
    ci::Vec2f mWind;
    
    VectorArrow * mArrow;
    
};

void NOC_4_08_ParticleSystemSmokeApp::setup()
{
    setFrameRate(30.);
    mParticleSystems.push_back( new ParticleSystem( ci::Vec2f (getWindowWidth()/2, 2*getWindowHeight()/3 ) ) ) ;
    mWind = ci::Vec2f (0, 0);
    ci::Vec2f arrowlocation = ci::Vec2f ( getWindowWidth()/2, getWindowHeight() - 50);
    mArrow = new VectorArrow( mWind, arrowlocation, 500);
}

// Mouse interaction:
void NOC_4_08_ParticleSystemSmokeApp::mouseDown( MouseEvent event )
{
    mParticleSystems.push_back( new ParticleSystem( event.getPos() ));
}

void NOC_4_08_ParticleSystemSmokeApp::mouseMove( MouseEvent event ) {
    mMousePos = event.getPos();
}

void NOC_4_08_ParticleSystemSmokeApp::mouseDrag( MouseEvent event ) {
    mMousePos = event.getPos();
}

void NOC_4_08_ParticleSystemSmokeApp::keyDown( KeyEvent event) {
    if ( event.getChar() == 'x') {
        mParticleSystems.clear();
    }
}

void NOC_4_08_ParticleSystemSmokeApp::update()
{
    float dx = ci::lmap<float>( mMousePos.x, 0, getWindowWidth(), -0.2, 0.2);
    mWind = ci::Vec2f (dx, 0);
    mArrow->update( mWind );
    
    for (auto ps : mParticleSystems ) {
        ps->applyForce( mGravityForce );
        ps->applyForce( mWind );
        ps->update();
    }
}

void NOC_4_08_ParticleSystemSmokeApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    mArrow->draw();
    for (auto ps : mParticleSystems ) {
        ps->draw();
    }
}




CINDER_APP_NATIVE( NOC_4_08_ParticleSystemSmokeApp, RendererGl )
