// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 5-2: Boxes hitting boundaries

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Box2d.h"
#include "Box.h"
#include "Boundary.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_5_2_BoxesApp : public AppNative {
  public:
	void setup();
    void prepareSettings ( Settings * settings);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    b2Vec2 gravity = b2Vec2( 0.f, 10.f );
    b2World mWorld = b2World( gravity );
    
    std::vector<Box *> mBoxes; // container for our boxes
    std::vector<Boundary *> mBoundaries; // contains walls
    
    const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
};

void NOC_5_2_BoxesApp::setup()
{
//    setFrameRate(2.);
    // Add a bunch of fixed boundaries
//    boundaries.add(new Boundary(width/4,height-5,width/2-50,10));
//    boundaries.add(new Boundary(3*width/4,height-50,width/2-50,10));
    
    mBoundaries.push_back( new Boundary( 500, 300, 200, 10, mWorld ) );
    mBoundaries.push_back( new Boundary( 400, 500, 300, 10, mWorld ) );
    mBoundaries.push_back( new Boundary( 600, 400, 300, 10, mWorld ) );

//    mBoundaries.push_back( new Boundary( getWindowWidth()/4, getWindowHeight()-5, getWindowWidth()/2-50, 10, mWorld ) );
//    mBoundaries.push_back( new Boundary(3*getWindowWidth()/4, getWindowHeight()-50, getWindowWidth()/2-50, 10, mWorld ) );
}

void NOC_5_2_BoxesApp::prepareSettings( Settings * settings ) {
    settings->setWindowSize(800, 600);
}

void NOC_5_2_BoxesApp::mouseDown( MouseEvent event )
{
}

void NOC_5_2_BoxesApp::update()
{
    // Step forward in time:
    mWorld.Step(timeStep, velocityIterations, positionIterations);
    
    // Boxes fall from the top every so often (0.2 = 20% of frames)
    if (ci::randFloat() < 0.2 ) {
        mBoxes.push_back( new Box( ci::Vec2f( getWindowWidth()/2, 30 ), mWorld ));
    }
    for (auto box: mBoxes) {
        box->update();
    }
}


void NOC_5_2_BoxesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    // Draw wall boundaries:
    for (auto wall : mBoundaries) {
        wall->draw();
    }
    // go through all the boxes and check whether they need to die or be drawn:
    for (int i = 0; i < mBoxes.size(); i++){
        if (mBoxes.at(i)->isDead()){
            delete mBoxes.at(i);
            mBoxes.erase( mBoxes.begin()+i );
        } else
            mBoxes.at(i)->draw();        
    }
}

CINDER_APP_NATIVE( NOC_5_2_BoxesApp, RendererGl )
