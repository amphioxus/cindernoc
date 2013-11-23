/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 9-1: Genetic Algorithm: Evolving Shakespeare
 
 */

#include <sstream>

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Population.h"

#include "cinder/gl/TextureFont.h"
#include "cinder/Font.h"
#include "cinder/Text.h"

using namespace ci;
using namespace ci::app;
using namespace std;

static const bool PREMULT = false;

class NOC_9_01_GAApp : public AppNative {
    Population * mPopulation;
    int mPopulationMax;
    float mMutationRate;
    bool isPaused = false;
    
    // for the text layout on the left:
    gl::Texture mTextureLeft;
	std::string normalFont;
	std::string boldFont;
    std::string mPopDisplay, mMutDisplay;
    // for the text box on the right:
    Font mFont;
    gl::Texture	mTextureRight;
    
  public:
	void setup();
    void prepareSettings( Settings * settings );
	void mouseDown( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    void renderText();
};

void NOC_9_01_GAApp::setup()
{
    std::string target = "To be or not to be.";
    mPopulationMax = 300;
    // std::string can't easily convert from integers or float, therefore I'm turning
    // the numbers into strings via an ostringstream object:
    std::ostringstream ss;
    ss << mPopulationMax;
    mPopDisplay = ss.str();
    mMutationRate = 0.01;
    std::ostringstream ssm;
    ssm << mMutationRate;
    mMutDisplay = ssm.str();
    mPopulation = new Population( target, mMutationRate, mPopulationMax );
    
    // set up Fonts:
    
	normalFont =  "Courier";
	boldFont = "Courier-Bold";
    mFont = Font( "Courier", 14 );
}

void NOC_9_01_GAApp::prepareSettings( Settings *settings ) {
    settings->setWindowSize(800, 400);
//    settings->setWindowPos(100, 100);
    settings->setResizable( false );
}


void NOC_9_01_GAApp::mouseDown( MouseEvent event )
{
}

void NOC_9_01_GAApp::keyDown( KeyEvent event ) {
    // show fitness of each member (debug)
    if ( event.getChar() == 'i' ) {
        std::cout << mPopulation->getInfo() << std::endl;
    } else if ( event.getCode() == KeyEvent::KEY_SPACE ) {
        isPaused = !isPaused;
    } else if ( event.getChar() == 'r' ) {
        mPopulation->resetPopulation();
    }
}


void NOC_9_01_GAApp::update()
{
    if (!isPaused && !mPopulation->isFinished() ) {
        mPopulation->applyNaturalSelection();
        mPopulation->generate();
        mPopulation->calculateFitness();
    }

    renderText();
}

void NOC_9_01_GAApp::draw()
{
	// this pair of lines is the standard way to clear the screen in OpenGL
	glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
    gl::enableAlphaBlending( PREMULT );
	gl::setMatricesWindow( getWindowSize() );

	gl::draw( mTextureLeft, Vec2f( 20, 10 ) );
    if( mTextureRight )
		gl::draw( mTextureRight, Vec2f( 380, 10 ) );

}

void NOC_9_01_GAApp::renderText() {
    
    TextLayout layout;
    layout.clear( ColorA(0, 0, 0, 0 ) );
    layout.setFont( Font( normalFont, 24 ) );
    layout.setColor( Color( .4, .4, .4 ) );
    layout.setLeadingOffset( 10 );
    layout.addLine( "Best phrase:" );
    layout.setFont( Font( boldFont, 36 ) );
    layout.setColor( Color( .2, .5, .8 ) );
    layout.addLine( mPopulation->getBest() );
    layout.addLine(" ");
    layout.addLine(" ");
    
    layout.setFont( Font( normalFont, 18 ) );
    layout.setColor( Color( .4, .4, .4 ) );
    if (isPaused && !mPopulation->isFinished() ) layout.addLine("Paused");
    else if ( isPaused && mPopulation->isFinished() ) layout.addLine("Paused (FINISHED. Press 'R' to reset.)");
    else if ( !isPaused && mPopulation->isFinished()) layout.addLine( "FINISHED. Press 'R' to reset." );
    else layout.addLine( "RUNNING" );
    std::ostringstream gens;
    gens <<  "Total generations: " << mPopulation->getGenerations() << "\n";
    std::string generations( gens.str() );
    layout.addLine( generations );
    
    std::ostringstream fmax;
    fmax << "Best fitness: " << mPopulation->getFittest();
    std::string maxFit( fmax.str() );
    layout.addLine( maxFit );
    
    std::ostringstream afit;
    afit << "Average fitness: " << mPopulation->getAverageFitness() ;
    std::string avrgFitness( afit.str() );
    layout.addLine( avrgFitness );
    
    layout.addLine("Total population: " + mPopDisplay);
    layout.addLine("Mutation rate: " + mMutDisplay);
    
    layout.setFont( Font( normalFont, 12 ) );
    layout.addLine("Press 'R' to reset, 'Space' to pause");
    
    Surface8u rendered = layout.render( true, PREMULT );
	mTextureLeft = gl::Texture( rendered );
    
    // text box with a bunch of current sequences
    TextBox tbox = TextBox().alignment( TextBox::RIGHT).font( mFont ).size( Vec2i( 400, TextBox::GROW ) ).text( mPopulation->getAllSequences() );
	tbox.setColor( Color( .3, .3, .3 ) );
	mTextureRight = gl::Texture( tbox.render() );

}



CINDER_APP_NATIVE( NOC_9_01_GAApp, RendererGl )
