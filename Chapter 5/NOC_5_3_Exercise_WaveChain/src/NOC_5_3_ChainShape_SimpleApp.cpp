/** 
 The Nature of Code
 Daniel Shiffman

 Examples ported to Cinder ( http://libcinder.org )

 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)

 Example 5-3: Simple ChainShapes (hardcoded vertices)
 
*/

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"
#include "Box2d.h"
#include "Particle.h"
#include "Surface.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_5_3_ChainShape_SimpleApp : public AppNative {
    
    // Values for iterating through time in Box2D world
    const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
    
  public:
    
    b2Vec2 gravity = b2Vec2( 0.f, 10.f );
    b2World mWorld = b2World( gravity );

    
    std::vector<Particle *> mParticles;  // container for particles
    box2d::Surface *surface;
    
	void setup();
    void prepareSettings( Settings * settings);
	void mouseDown( MouseEvent event );
    void mouseDrag( MouseEvent event );
	void update();
	void draw();
};


void NOC_5_3_ChainShape_SimpleApp::setup()
{
    std::vector<ci::Vec2f> s;
    float angle = 0;
    for (int x = 50; x < getWindowWidth()-50; x++) {
        s.push_back( ci::Vec2f( x,
                                ci::lmap<float>( ci::math<float>::cos(angle), -1., 1., 300, 400) ));
        angle += 0.02;
    }
    
    surface = new box2d::Surface( s, mWorld );
}


void NOC_5_3_ChainShape_SimpleApp::prepareSettings( Settings * settings) {
    settings->setWindowSize(800, 600);
//    settings->setFrameRate(60.);
}


void NOC_5_3_ChainShape_SimpleApp::mouseDown( MouseEvent event )
{
    mParticles.push_back( new Particle( event.getPos(), 12.0, mWorld ) );
}


void NOC_5_3_ChainShape_SimpleApp::mouseDrag( MouseEvent event )
{
    mParticles.push_back( new Particle( event.getPos(), 12.0, mWorld ) );
}


void NOC_5_3_ChainShape_SimpleApp::update()
{
    // Step forward in time:
    mWorld.Step(timeStep, velocityIterations, positionIterations);
    // create particles:
    if (randFloat() < 0.2 ) {
        mParticles.push_back( new Particle( ci::Vec2f(getWindowWidth()/2, 20), 12.0, mWorld ) );
    }
    // delete or update particles:
    for (int i=0; i < mParticles.size(); i++) {
        if (mParticles.at(i)->isDead()) {
            delete mParticles.at(i);
            mParticles.erase(mParticles.begin()+i);
        } else
            mParticles.at(i)->update();        
    }      
}


void NOC_5_3_ChainShape_SimpleApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    surface->draw();
    
    for (auto p : mParticles) {
        p->draw();
    }
    
}

CINDER_APP_NATIVE( NOC_5_3_ChainShape_SimpleApp, RendererGl )
