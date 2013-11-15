/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 8-6: Recursive Tree

 // Renders a simple tree-like structure via recursion
 // Branching angle calculated as a function of horizontal mouse location

 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_8_06_TreeApp : public AppNative {
  public:
    float mTheta = M_PI_4;
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
	void update();
    void drawBranch( float len );
	void draw();
};

void NOC_8_06_TreeApp::setup()
{
}

void NOC_8_06_TreeApp::mouseDown( MouseEvent event )
{
}

void NOC_8_06_TreeApp::mouseMove( MouseEvent event ) {
    mTheta = lmap<float>(event.getX(), 0, getWindowWidth(), 0, M_PI_2);
    mTheta = ci::math<float>::clamp(mTheta, 0, M_PI_2); // keep it constrained in case mouse is off window
//    std::cout << mTheta << std::endl; // debug
}

void NOC_8_06_TreeApp::update()
{
}

void NOC_8_06_TreeApp::drawBranch( float len ) {
    gl::drawLine( Vec2f(0,0), Vec2f(0, -len));
    gl::translate(0, -len);
    len *= 0.66; // Each branch will be 2/3rds the size of the previous one
    // All recursive functions must have an exit condition!!!!
    // Here, ours is when the length of the branch is 2 pixels or less
    if ( len > 2 ) {
        gl::pushMatrices();              // Save the current state of transformation (i.e. where are we now)
        gl::rotate( toDegrees(mTheta) ); // Rotate by theta
        drawBranch( len );               // Ok, now call myself to draw two new branches!!
        gl::popMatrices();               // Whenever we get back here, we "pop" in order to restore the previous matrix state
        
         // Repeat the same thing, only branch off to the "left" this time!
        gl::pushMatrices();
        gl::rotate( toDegrees( -mTheta) );
        drawBranch( len );
        gl::popMatrices();
    }
}


void NOC_8_06_TreeApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    gl::pushMatrices();
    gl::translate( getWindowWidth()/2, getWindowHeight() );
    
    ci::gl::color(1, 0, 0);
    drawBranch( 150 );
    gl::popMatrices();
}

CINDER_APP_NATIVE( NOC_8_06_TreeApp, RendererGl )
