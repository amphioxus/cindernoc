// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)

// Example 3-7: Oscillating objects

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Oscillator.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_3_07_oscillating_objectsApp : public AppNative {
  public:
    void prepareSettings( Settings *settings);
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
//    Oscillator *oscillator;
    std::deque<OscillatorRef> oscillators; // using shared pointer to reference oscillator objects
};


void NOC_3_07_oscillating_objectsApp::prepareSettings(Settings *settings) {
    settings->setWindowSize(800, 600);
    settings->setFrameRate(60.);
}

void NOC_3_07_oscillating_objectsApp::setup()
{
    for (int i = 0; i < 20; i++) {
        auto osci = OscillatorRef( new Oscillator() );
        oscillators.push_back(osci);
    }
}


void NOC_3_07_oscillating_objectsApp::mouseDown( MouseEvent event )
{
}

void NOC_3_07_oscillating_objectsApp::update()
{
    for (auto osci : oscillators) {
        osci->oscillate();
    }
}

void NOC_3_07_oscillating_objectsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
  
    for ( auto osci : oscillators) {
        osci->draw();
    }
    
}

CINDER_APP_NATIVE( NOC_3_07_oscillating_objectsApp, RendererGl )
