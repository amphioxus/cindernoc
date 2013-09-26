#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Box2d.h"
#include "Boundary.h"
#include "CustomShape.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_5_4_PolygonsApp : public AppNative {
    
    std::vector<CustomShape *> mPolygons;
    std::vector<box2d::Boundary *> mBoundaries;
    std::vector<ci::Vec2f> mPolyshape;
    b2Vec2 gravity = b2Vec2( 0.f, 10.f );
    b2World mWorld = b2World( gravity );
    
    // Values for iterating through time in Box2D world
    const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
    
  public:
	void setup();
    void prepareSettings( Settings * settings );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};


void NOC_5_4_PolygonsApp::setup()
{
    // create PolyShape for CustomShape object.
    // NOTE: * vertices have to be ordered CCW
    //       * shape has to be concave
    mPolyshape.push_back( ci::Vec2f(-10, -10) );
    mPolyshape.push_back( ci::Vec2f(20, -15) );
    mPolyshape.push_back( ci::Vec2f(15, 0) );
    mPolyshape.push_back( ci::Vec2f(-15, 25) );
    
    // create boundary:    
    std::vector<ci::Vec2f> s;
    s.push_back(ci::Vec2f(250, 450));
    s.push_back(ci::Vec2f(getWindowWidth()/2, 500));
    s.push_back(ci::Vec2f(getWindowWidth()-100, 400));
    
    mBoundaries.push_back( new box2d::Boundary(s, mWorld));

    
    // another boundary:
    std::vector<ci::Vec2f> s2;
    s2.push_back(ci::Vec2f(30, 200));
    s2.push_back(ci::Vec2f(150, 300));
    s2.push_back(ci::Vec2f(200, 320));
    
    mBoundaries.push_back( new box2d::Boundary(s2, mWorld));
    
}

void NOC_5_4_PolygonsApp::prepareSettings( Settings * settings) {
    settings->setWindowSize(800, 600);
}

void NOC_5_4_PolygonsApp::mouseDown( MouseEvent event )
{
    mPolygons.push_back( new CustomShape( mPolyshape, event.getPos(), mWorld ) );
}

void NOC_5_4_PolygonsApp::update()
{
    // Step forward in time:
    mWorld.Step(timeStep, velocityIterations, positionIterations);
    
    for (int i=0; i < mPolygons.size(); i++) {
        if (mPolygons.at(i)->isDead()){
            delete mPolygons.at(i);
            mPolygons.erase(mPolygons.begin()+i);
        } else
            mPolygons.at(i)->update();
    }
    
}

void NOC_5_4_PolygonsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    for (auto p : mPolygons) {
        p->draw();
    }
    
    for (auto b : mBoundaries) {
        b->draw();
    }
}

CINDER_APP_NATIVE( NOC_5_4_PolygonsApp, RendererGl )
