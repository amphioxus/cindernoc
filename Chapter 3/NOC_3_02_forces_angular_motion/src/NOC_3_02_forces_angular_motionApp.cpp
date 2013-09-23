// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 3-02: Angular motion with forces

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Mover.h"
#include "Attractor.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_3_02_forces_angular_motionApp : public AppBasic {
public:
	void setup();
	void update();
	void draw();
    void prepareSettings(Settings *settings);
    
    void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void mouseUp( MouseEvent event );
    
    
    std::vector<Mover *> mMovers;
    std::vector<Attractor *> mAttractors;
    
    ci::Vec2f mousePos;
};

void NOC_3_02_forces_angular_motionApp::prepareSettings(Settings *settings) {
    settings->setWindowSize(800, 600);
}

void NOC_3_02_forces_angular_motionApp::setup()
{
    int numMovers = 10;
    for (int i = 0; i < numMovers; i++) {
        mMovers.push_back( new Mover(randFloat(0.5, 3), randFloat( getWindowWidth() ), randFloat( getWindowHeight() ) ) );
    }
    
    // add  attractors
    mAttractors.push_back( new Attractor() );
    mAttractors.push_back( new Attractor( ci::Vec2f (100.,100.), 25.0 ) );
}

void NOC_3_02_forces_angular_motionApp::mouseDown( MouseEvent event ) {
    
    for ( auto attractor : mAttractors) {
        attractor->clicked( event.getPos() );
    }
}

void NOC_3_02_forces_angular_motionApp::mouseMove( MouseEvent event ) {
    mousePos = event.getPos();
}

void NOC_3_02_forces_angular_motionApp::mouseDrag( MouseEvent event ) {
    // call mousemove to get mouse position while dragging:
    mouseMove(event);
    
    for ( auto attractor : mAttractors) {
        attractor->dragged(mousePos);
    }
    
}

void NOC_3_02_forces_angular_motionApp::mouseUp( MouseEvent event ) {
    
    for ( auto attractor : mAttractors) {
        attractor->mouseup();
    }
}

void NOC_3_02_forces_angular_motionApp::update()
{
    for (auto mover : mMovers) {
        // go through each attractor to calculate force towards it:
        for (auto attractor : mAttractors) {
            attractor->hover(mousePos);
            Vec2f f = attractor->attract(mover);
            mover->applyForce(f);
        }

        // update the mover after collecting all the forces:
        mover->update();
    }
    
}

void NOC_3_02_forces_angular_motionApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
    for (auto mover : mMovers) {
        mover->draw();
        mover->draw_history();
    }
    
    for ( auto attractor : mAttractors) {
        attractor->draw();
    }
    
}



CINDER_APP_NATIVE( NOC_3_02_forces_angular_motionApp, RendererGl )
