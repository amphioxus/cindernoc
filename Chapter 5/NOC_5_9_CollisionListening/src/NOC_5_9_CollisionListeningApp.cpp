#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "Box2d.h"
#include "Particle.h"
#include "Boundary.h"
#include "CollisionListener.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_5_9_CollisionListeningApp : public AppNative {
    b2Vec2 gravity = b2Vec2 (0., 10);
    b2World mWorld = b2World( gravity );
    
    std::vector<Particle *> mParticles;
    Boundary * mBoundary;
    CollisionListener mContactListener;
    
    // Values for iterating through time in Box2D world
    const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;

  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void NOC_5_9_CollisionListeningApp::setup()
{
    Rectf rect = Rectf( 0, getWindowHeight()-20, getWindowWidth(), getWindowHeight());
    mBoundary = new Boundary( rect, mWorld );
    mWorld.SetContactListener( &mContactListener );
}

void NOC_5_9_CollisionListeningApp::mouseDown( MouseEvent event )
{
}

void NOC_5_9_CollisionListeningApp::update()
{
    // Step forward in time:
    mWorld.Step(timeStep, velocityIterations, positionIterations);

    if (randFloat() < 0.1 ) {
        mParticles.push_back( new Particle(Vec2f( randFloat(0, getWindowWidth() ), 30),
                                           randFloat(8., 16.),
                                           mWorld ) );
    }
    // update or kill particles:
    for (int i = 0; i < mParticles.size(); i++) {
        if (mParticles.at(i)->isDead()){
            delete mParticles.at(i);
            mParticles.erase(mParticles.begin() + i);
        } else
        mParticles.at(i)->update();
    }
}


void NOC_5_9_CollisionListeningApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    mBoundary->draw();
    for ( auto p : mParticles ) {
        p->draw();
    }
}

CINDER_APP_NATIVE( NOC_5_9_CollisionListeningApp, RendererGl )
