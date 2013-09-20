#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_3_09_waveApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    float startAngle = 0;
    float angleVel = 0.23;

};

void NOC_3_09_waveApp::setup()
{
}

void NOC_3_09_waveApp::mouseDown( MouseEvent event )
{
}

void NOC_3_09_waveApp::update()
{
}

void NOC_3_09_waveApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    
    startAngle += 0.015;
    float angle = startAngle;
    
    for (int x = 0; x <= getWindowWidth(); x += 24) {
        float y = lmap<float>( math<float>::sin( angle ), -1, 1, 0,  getWindowHeight() );
        gl::color(.8, .6, .6);
        gl::drawSolidCircle( ci::Vec2f (x,y), 12.0);
        angle += angleVel;
    }

}

CINDER_APP_NATIVE( NOC_3_09_waveApp, RendererGl )
