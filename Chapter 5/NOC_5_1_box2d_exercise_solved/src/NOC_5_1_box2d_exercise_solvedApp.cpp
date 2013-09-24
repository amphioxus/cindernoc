#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Box2d.h"
#include "Box.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_5_1_box2d_exercise_solvedApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseDrag (MouseEvent event );
	void update();
	void draw();
    
    b2Vec2 gravity = b2Vec2(0.0f, 3.f);
    b2World mWorld = b2World( gravity ); // set up a Box2D world
    
    std::vector<Box *> mBoxes; // container for our boxes
    
};

void NOC_5_1_box2d_exercise_solvedApp::setup()
{
    setFrameRate(30.);
}

void NOC_5_1_box2d_exercise_solvedApp::mouseDown( MouseEvent event )
{
    mBoxes.push_back( new Box( event.getPos(), mWorld ) );
}

void NOC_5_1_box2d_exercise_solvedApp::mouseDrag( MouseEvent event )
{
    mBoxes.push_back( new Box( event.getPos(), mWorld ) );
}

void NOC_5_1_box2d_exercise_solvedApp::update()
{
    // Nathan Koch's example showed me to use timeStep and iteration variables with the Step method:
    float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
    
    mWorld.Step(timeStep, velocityIterations, positionIterations);
    
    for (auto box : mBoxes) {
        if (!box->isDead()) {
            box->update();
        }         
    }
}

void NOC_5_1_box2d_exercise_solvedApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    for (auto box : mBoxes) {
        box->draw();
    }
    
}

CINDER_APP_NATIVE( NOC_5_1_box2d_exercise_solvedApp, RendererGl )
