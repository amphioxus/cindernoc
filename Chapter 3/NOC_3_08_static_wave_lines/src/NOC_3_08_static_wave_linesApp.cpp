#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_3_08_static_wave_linesApp : public AppNative {
  public:
    void prepareSettings(Settings *settings);
	void setup();
	void mouseDown( MouseEvent event );
    void keyDown (KeyEvent event);
	void update();
    void recalculate();
	void draw();
    
    float mAngle = 0;
    float mAngleVelocity = 0.1;
    std::vector<ci::Vec2f>  mWaveform;
};

void NOC_3_08_static_wave_linesApp::prepareSettings( Settings *settings) {
    settings->setWindowSize(800, 600);
}

void NOC_3_08_static_wave_linesApp::setup()
{
    recalculate();
}

void NOC_3_08_static_wave_linesApp::mouseDown( MouseEvent event )
{
}

void NOC_3_08_static_wave_linesApp::keyDown(KeyEvent event){
 
    if ( event.getChar() == 'f' ) {
        // Toggle between full-screen and window:
        setFullScreen( ! isFullScreen() );
        recalculate();
    }
    else if (event.getChar() == 'u') {
        mAngleVelocity += 0.01;
        recalculate();
    }
    else if (event.getChar() == 'i') {
        mAngleVelocity -= 0.01;
        recalculate();
    }
        
}


void NOC_3_08_static_wave_linesApp::recalculate(){
    
    mWaveform.clear();
    
    for (int i = 0; i < getWindowWidth(); i += 1) {
        
        mWaveform.push_back( ci::Vec2f (i,
                                        lmap<float>( math<float>::sin( mAngle ), -1., 1., 0, getWindowHeight() )
                                        )
                            );
        
        mAngle += mAngleVelocity;
    }
    
    
}


void NOC_3_08_static_wave_linesApp::update()
{
}

void NOC_3_08_static_wave_linesApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
    gl::color( Color( 1.0f, 0.5f, 0.25f ) );
    gl::draw( mWaveform );
    
}

CINDER_APP_NATIVE( NOC_3_08_static_wave_linesApp, RendererGl )
