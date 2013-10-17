/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 5-8: Mouse Joints
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Box2d.h"
#include "Boundary.h"
#include "Box.h"
#include "Spring.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_5_8_MouseJointApp : public AppNative {
    std::vector<Boundary *> mBoundaries;
    Box * mBox;
    Spring * mSpring;
    b2Vec2 gravity = b2Vec2(0,10);
    b2World mWorld = b2World( gravity );
    
    // Values for iterating through time in Box2D world
    const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
    
  public:
	void setup();
    void prepareSettings( Settings * settings );
	void mouseDown( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void mouseUp( MouseEvent event );
	void update();
	void draw();
};

void NOC_5_8_MouseJointApp::setup()
{
    // create boundaries around the window:
    std::vector<ci::Rectf> rects;
    rects.push_back( ci::Rectf(10, 10, 780, 20) );
    rects.push_back( ci::Rectf(10, 10, 20, 580));
    rects.push_back( ci::Rectf(10, 580, 780, 590));
    rects.push_back( ci::Rectf(780, 10, 790, 590));
    for (auto r : rects) {
        mBoundaries.push_back( new Boundary(r, 0, mWorld));
    }
    
    // create box:
//    Box( ci::Vec2f location, float w, float h, bool lock, b2World &world); 
    mBox = new Box( ci::Vec2f(400, 50), 24., 24., FALSE, mWorld);
    
    // get Spring ready
    mSpring = new Spring( mWorld );
    
}

void NOC_5_8_MouseJointApp::prepareSettings( Settings * settings ) {
    settings->setWindowSize(800, 600);
//    settings->isBorderless();
    settings->setResizable(FALSE);
}

// Mouse interaction methods follow:
void NOC_5_8_MouseJointApp::mouseDown( MouseEvent event )
{
    if ( mBox->contains( event.getPos() ) ) {
//        std::cout << "INside" << std::endl; // debug
        mSpring->bind( event.getPos(), *mBox );
    }
}

void NOC_5_8_MouseJointApp::mouseDrag( MouseEvent event )
{
    mSpring->update( event.getPos() );
}

void NOC_5_8_MouseJointApp::mouseUp( MouseEvent event )
{
    mSpring->destroy();
}


void NOC_5_8_MouseJointApp::update()
{
    // Step forward in time:
    mWorld.Step(timeStep, velocityIterations, positionIterations);
    
    mBox->update();
    
    
}

void NOC_5_8_MouseJointApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    for (auto b : mBoundaries) {
        b->draw();
    }
    
    mBox->draw();
    mSpring->draw();
}

CINDER_APP_NATIVE( NOC_5_8_MouseJointApp, RendererGl )
