/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 8-7: Stochastic Recursive Tree
 
 // Renders a simple tree-like structure via recursion
 // Mouse click resets the tree and draws another random one
 
 */


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_8_07_TreeStochasticApp : public AppNative {
  public:
    float mTheta;
    bool alreadyDrawn = false;
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void drawBranch( float len );
};

void NOC_8_07_TreeStochasticApp::setup()
{
}

void NOC_8_07_TreeStochasticApp::mouseDown( MouseEvent event )
{
    alreadyDrawn = false;
}

void NOC_8_07_TreeStochasticApp::update()
{
}

void NOC_8_07_TreeStochasticApp::draw()
{
    if (!alreadyDrawn) {
        gl::enableAlphaBlending();
        // clear out the window with black
        gl::clear( Color( 0, 0, 0) );
        // draw from the bottom of the screen
        gl::pushMatrices();
        gl::translate( getWindowWidth()/2, getWindowHeight() );
        gl::color( ColorA(1, 0, 0, 0.4)) ;
        drawBranch( 160 );
        gl::popMatrices();
        gl::disableAlphaBlending();
        alreadyDrawn = true;
    }
}

void NOC_8_07_TreeStochasticApp::drawBranch( float len ) {
    float lineW = ci::lmap<float>(len, 0, 160, 1, 5);
    gl::lineWidth(lineW);
    gl::drawLine( Vec2f(0,0), Vec2f(0, -len));
    gl::translate(0, -len);
    len *= 0.66; // Each branch will be 2/3rds the size of the previous one
    // All recursive functions must have an exit condition!!!!
    // Here, ours is when the length of the branch is 2 pixels or less
    if ( len > 2 ) {
                // a random number of branches:
        for (int i=0; i < ci::randInt(1, 5); i++) {
            mTheta = ci::randFloat(-90.f, 90.f);
            gl::pushMatrices();              // Save the current state of transformation (i.e. where are we now)
            gl::rotate( mTheta ); // Rotate by theta
            drawBranch( len );               // Ok, now call myself to draw two new branches!!
            gl::popMatrices();               // Whenever we get back here, we "pop" in order to restore the previous matrix state
        }
    }
}


CINDER_APP_NATIVE( NOC_8_07_TreeStochasticApp, RendererGl )
