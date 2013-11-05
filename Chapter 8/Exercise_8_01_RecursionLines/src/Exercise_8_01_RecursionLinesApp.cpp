/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Exercise 8-1:  Recursion Lines
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Exercise_8_01_RecursionLinesApp : public AppNative {
  public:
    bool alreadyDrawn = false;
	void setup();
    void prepareSettings( Settings * settings);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void drawLines(float x1, float y1, float x2, float y2);
};

void Exercise_8_01_RecursionLinesApp::setup()
{
    
}

void Exercise_8_01_RecursionLinesApp::prepareSettings( Settings *settings) {
    settings->setResizable(false);
    settings->setWindowSize(800, 600);
}

void Exercise_8_01_RecursionLinesApp::mouseDown( MouseEvent event )
{
}

void Exercise_8_01_RecursionLinesApp::update()
{
}

void Exercise_8_01_RecursionLinesApp::draw()
{
    gl::enableAlphaBlending();
    if (alreadyDrawn == false ) {
        // clear out the window with black
        gl::clear( Color( 0, 0, 0 ) );
        gl::color(1, 0, 0);
        drawLines(100,300,700,300);
    }
    gl::disableAlphaBlending();
}


void Exercise_8_01_RecursionLinesApp::drawLines(float x1, float y1, float x2, float y2) {
    
    gl::drawLine(Vec2f(x1, y1), Vec2f(x2, y2));
    
    float dx = x2 - x1;
    float dy = y2 - y1;
    
    if (dx == 0 && dy > 4 ) {
        drawLines(x1-dy/3, y1, x1+dy/3, y1);
        drawLines(x1-dy/3, y2, x1+dy/3, y2);
    } else if (dy == 0 && dx > 4 ) {
        drawLines(x1, y1-dx/3, x1, y1+dx/3);
        drawLines(x2, y1-dx/3, x2, y1+dx/3);
    }
}


CINDER_APP_NATIVE( Exercise_8_01_RecursionLinesApp, RendererGl )
