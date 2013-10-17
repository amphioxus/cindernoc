/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 6-4: Flow field following
 
*/

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Vehicle.h"
#include "FlowField.h"
#include "Common.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class NOC_6_04_FlowfieldApp : public AppNative {
    
protected:
    FlowField *mFlowField;
    std::vector<Vehicle *> mVehicles;
    bool DRAW_GRID = false;
    bool DRAW_VECTORS = true;
    bool DRAW_HISTORY = true;
public:
    // methods:
	void setup();
    void prepareSettings( Settings * settings);
	void mouseDown( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void keyDown( KeyEvent event);
	void update();
	void draw();
};

void NOC_6_04_FlowfieldApp::setup()
{
    mFlowField = new FlowField( 20 );
}

void NOC_6_04_FlowfieldApp::prepareSettings(Settings * settings) {
    settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
    settings->setResizable( false );
    settings->setTitle("Flow Field");
//    settings->setFrameRate(30);
}
void NOC_6_04_FlowfieldApp::mouseDown( MouseEvent event )
{
    mVehicles.push_back( new Vehicle( event.getPos() ) );
//    std::cout << mFlowField->lookup( event.getPos() ) << std::endl; // debug
}


void NOC_6_04_FlowfieldApp::mouseDrag( MouseEvent event ) {
    mVehicles.push_back( new Vehicle( event.getPos() ) );
}

void NOC_6_04_FlowfieldApp::keyDown(KeyEvent event ) {
    if (event.getChar() == 'x') {
        mFlowField->init();
    } else if (event.getChar() == 'g') {
        DRAW_GRID = !DRAW_GRID;
    } else if (event.getChar() == 'v') {
        DRAW_VECTORS = !DRAW_VECTORS;
    } else if (event.getChar() == 'h')  {
        DRAW_HISTORY = !DRAW_HISTORY;
    }
}


void NOC_6_04_FlowfieldApp::update()
{
    for (auto v : mVehicles) {
        v->follow( mFlowField );
        v->update();
    }
}

void NOC_6_04_FlowfieldApp::draw()
{
//    std::cout << getFrameRate() << std::endl; // debug
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    if (DRAW_VECTORS) { mFlowField->draw(); }
    if (DRAW_GRID) { mFlowField->drawGrid(); }
    
    for (int i=0; i < mVehicles.size(); i++) {
        Vehicle *v = mVehicles.at(i);
        if (v->isDead()) {
            mVehicles.erase( mVehicles.begin() + i);
        } else {
            if (DRAW_HISTORY) {
                v->drawHistory();
            }
            v->draw();
        }
    }
}


CINDER_APP_NATIVE( NOC_6_04_FlowfieldApp, RendererGl )
