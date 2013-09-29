#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Font.h"
#include "Box2d.h"
#include "Particle.h"
#include "Windmill.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_5_7_RevoluteJointApp : public AppNative {
    
    b2Vec2 gravity = b2Vec2 (0., 10);
    b2World mWorld = b2World( gravity );
    Windmill *windmill;
    std::vector<Particle *> mParticles;
    
    // Values for iterating through time in Box2D world
    const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
    
    // for displaying messages, set up fonts
    Font				mFont;
	gl::TextureFontRef	mTextureFont;

  public:
	void setup();
    void prepareSettings( Settings * settings );
	void mouseDown( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
};


void NOC_5_7_RevoluteJointApp::setup()
{
    // set up wind mill:
    windmill = new Windmill( ci::Vec2f( 400, 500), mWorld );
    // create font for displaying messages in window:
    mFont = Font( "Arial", 18 );
    mTextureFont = gl::TextureFont::create( mFont );
}


void NOC_5_7_RevoluteJointApp::prepareSettings(Settings * settings ) {
    settings->setWindowSize(800, 600);
}


void NOC_5_7_RevoluteJointApp::mouseDown( MouseEvent event )
{
    mParticles.push_back( new Particle( event.getPos(), 10.0, mWorld ) );
}


void NOC_5_7_RevoluteJointApp::keyDown( KeyEvent event ) {
    if (event.getChar() == 'x') {
        windmill->toggleMotor();
    }
}


void NOC_5_7_RevoluteJointApp::update()
{
    // Step forward in time:
    mWorld.Step(timeStep, velocityIterations, positionIterations);
    // create new Particles:
    if ( ci::randFloat() < 0.3 ) {
        mParticles.push_back( new Particle( ci::Vec2f(400, 50), ci::randFloat(5, 12), mWorld ));
    }
    
    windmill->update();
    for (int i = 0; i < mParticles.size(); i++) {
        if ( mParticles.at(i)->isDead() ) {
            delete mParticles.at(i);
            mParticles.erase(mParticles.begin() + i);
        } else
            mParticles.at(i)->update();        
    }
}


void NOC_5_7_RevoluteJointApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    windmill->draw();
    
    for (auto p : mParticles) {
        p->draw();
    }
    gl::color(1., 1., 1.);
    gl::enableAlphaBlending();
    mTextureFont->drawString( "Click 'x' to toggle motor", Vec2f( 10, 10 +  mTextureFont->getAscent() ) );
    string ms;
    if (windmill->motorOn())
        ms = "Motor: ON";
    else
        ms = "Motor: OFF";
    mTextureFont->drawString( ms, Vec2f( 10, 40 +  mTextureFont->getAscent() ) );
    gl::disableAlphaBlending();
}

CINDER_APP_NATIVE( NOC_5_7_RevoluteJointApp, RendererGl )
