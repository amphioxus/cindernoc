/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 6-5/6: Path following
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "Path.h"
#include "Vehicle.h"
#include "Common.h"


using namespace ci;
using namespace ci::app;
using namespace std;


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 400;

class NOC_6_06_PathFollowingApp : public AppNative {
    
    std::vector< Vec2f > mPathVertices;
    Path * mPath;
    std::vector< Vehicle * > mVehicles;
    
  public:
	void setup();
    void prepareSettings( Settings * settings );
	void mouseDown( MouseEvent event );
    void keyDown( KeyEvent event );
    void newPath();
	void update();
	void draw();
};

void NOC_6_06_PathFollowingApp::setup()
{
    
    newPath();
    
    mPath = new Path (mPathVertices, 20.f);

    mVehicles.push_back( new Vehicle( ci::Vec2f(50, 200), 6., 0.2 ) );
    
}

void NOC_6_06_PathFollowingApp::prepareSettings( Settings * settings ) {
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
}

void NOC_6_06_PathFollowingApp::mouseDown( MouseEvent event )
{
    mVehicles.push_back( new Vehicle( event.getPos(), 6., 0.2 ) );
}

void NOC_6_06_PathFollowingApp::keyDown( KeyEvent event ) {
    if (event.getChar() == 'x') {
        newPath();
        mPath->resetLine( mPathVertices );
    }
}

void NOC_6_06_PathFollowingApp::newPath() {
    
    if (!mPathVertices.empty()) {
        mPathVertices.clear();
    }
    mPathVertices.push_back( Vec2f ( -20, getWindowHeight()/2 ) );
    mPathVertices.push_back( Vec2f ( randFloat( 0, getWindowWidth()/2 ), randFloat(0, getWindowHeight() ) ) );
    mPathVertices.push_back( Vec2f ( randFloat( getWindowWidth()/2, getWindowWidth() ), randFloat(0, getWindowHeight() ) ) );
    mPathVertices.push_back( Vec2f ( getWindowWidth()+20, getWindowHeight()/2 ) );
}


void NOC_6_06_PathFollowingApp::update()
{
    for (auto v : mVehicles) {
        v->follow( mPath );
        v->update();
        v->checkBorders();
    }
}

void NOC_6_06_PathFollowingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 1, 1, 1 ) );
    
    mPath->draw();
    
    for (auto v : mVehicles ) {
        v->drawDebug();
        v->draw();
    }
}

CINDER_APP_NATIVE( NOC_6_06_PathFollowingApp, RendererGl )
