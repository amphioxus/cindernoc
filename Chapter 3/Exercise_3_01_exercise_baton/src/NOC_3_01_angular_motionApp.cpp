#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_3_01_angular_motionApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    float mAngle = 0;
    float mAngleVelocity = 0;
    float mAngleAcceleration = 0.0005;
};

void NOC_3_01_angular_motionApp::setup()
{
    setFrameRate(30.f);
    
}

void NOC_3_01_angular_motionApp::mouseDown( MouseEvent event )
{
    mAngleVelocity = 0;
}

void NOC_3_01_angular_motionApp::update()
{
    mAngle += mAngleVelocity;
    mAngleVelocity += mAngleAcceleration;
}

void NOC_3_01_angular_motionApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::pushMatrices();
    
    gl::translate( (Vec2f)app::getWindowCenter()   );
    gl::rotate( toDegrees(mAngle) );
    gl::color(.4, .4, .4);
    gl::lineWidth(4.f);
    gl::drawLine(Vec2f(-50.f, 0), Vec2f(50.f, 0));
    
    gl::drawSolidCircle( Vec2f(-50.,0), 12.);
    gl::drawSolidCircle( Vec2f(50.,0), 12.);
    gl::popMatrices();
    
    
}

CINDER_APP_NATIVE( NOC_3_01_angular_motionApp, RendererGl )
