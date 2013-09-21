// The Nature of Code
// Daniel Shiffman
//
// Examples ported to Cinder ( http://libcinder.org )
//
// Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
//
// Example 2-05: Fluid resistance

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Font.h"
#include "Mover.h"
#include "Liquid.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_2_5_fluidresistanceApp : public AppNative {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );
    void resize();
	void update();
	void draw();
    void reset_movers();
    void clear_movers();
    // TODO change to pointers:
    Liquid liquid;
    std::list<Mover> movers; // list to store mover objects
    
    Font				mFont;
	gl::TextureFontRef	mTextureFont;
};

void NOC_2_5_fluidresistanceApp::prepareSettings(Settings *settings) {
    settings->setTitle("Liquid drag");
    settings->setWindowSize( 800, 400 );
}

void NOC_2_5_fluidresistanceApp::setup()
{
    // place liquid at the bottom half of the window
    liquid = Liquid(0, getWindowHeight()/2., getWindowWidth(), getWindowHeight()/2., 0.1);
    // Enter Movers:
    reset_movers();
    
    mFont = Font( "Arial", 18 );
    mTextureFont = gl::TextureFont::create( mFont );
}

void NOC_2_5_fluidresistanceApp::mouseDown( MouseEvent event )
{
    if (event.isLeftDown()) {
        reset_movers();
    } else
        clear_movers();
    
}

void NOC_2_5_fluidresistanceApp::resize() {
    
    liquid.resize(0, getWindowHeight()/2., getWindowWidth(), getWindowHeight()/2.);
}

void NOC_2_5_fluidresistanceApp::update()
{
    for (std::list<Mover>::iterator it = movers.begin(); it != movers.end(); it++) {
        // check whether we are in fluid:
        if (liquid.contains( *it )) {
            // mover is in liquid, calculate drag
            ci::Vec2f drag = liquid.drag( *it );
            // and apply it to mover:
            it->apply_force( drag );
        }
        ci::Vec2f gravity (0, 0.1 * it->mMass );
        it->apply_force( gravity );
        
        it->update();               
    }
}

void NOC_2_5_fluidresistanceApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    for (std::list<Mover>::iterator it = movers.begin(); it != movers.end(); it++) {
        it->display();
        it->checkEdges();
    }
    
    liquid.display();
    
    // show text:
    gl::color(1., 1., 1.);
    gl::enableAlphaBlending();
    mTextureFont->drawString( "Left mouse: add more; Right mouse: reset", Vec2f( 10, 10 +  mTextureFont->getAscent() ) );
    
}

void NOC_2_5_fluidresistanceApp::reset_movers() {
     
    const int amount = 10;
    for (int i = 0; i < amount; i++ ) {
        
        movers.push_back( Mover( ci::randFloat(0.5, 3.), (getWindowWidth()/float(amount+1)) + (i*getWindowWidth()/float(amount+1)), 0 ) );
    }
    
}

void NOC_2_5_fluidresistanceApp::clear_movers() {
    movers.clear();
}


CINDER_APP_NATIVE( NOC_2_5_fluidresistanceApp, RendererGl )
