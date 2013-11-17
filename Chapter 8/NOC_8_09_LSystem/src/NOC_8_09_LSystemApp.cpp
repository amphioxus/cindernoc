/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Example 8-9 (and Exercise 8-12): L-System, with branches collected in std::vector container
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "LSystem.h"
#include "Rule.h"
#include "Turtle.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_8_09_LSystemApp : public AppNative {
    LSystem * mLSystem;
    std::vector<Rule> mRuleset;
    Turtle * mTurtle;
  public:
	void setup();
    void prepareSettings( Settings * settings);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void NOC_8_09_LSystemApp::setup()
{

    /*
     * Cantor Set as L-System:
     *
     * Alphabet: A B
     * Axiom: A
     * Rules: (A → ABA) (B → BBB)
     *
     */
    
//    mRuleset.push_back( Rule('A', "ABA") );
//    mRuleset.push_back( Rule('B', "BBB") );
//    mLSystem = new LSystem("A", mRuleset );
    
    
/*
 *  Alphabet: FG+-[]
 *     Axiom: F
 *    Rules: F -→ FF+[+F-F-F]-[-F+F+F]
 */
    
    mRuleset.push_back( Rule('F', "FF+[+F-F-F]-[-F+F+F]") );
    mLSystem = new LSystem("F", mRuleset );
    
//    std::cout << mLSystem->getSentence() << std::endl; // debug: print out first sentence

    // set up Turtle graphing object:
    mTurtle = new Turtle( mLSystem->getSentence(), getWindowHeight()/4, toRadians(25.f) );
    
    
}

void NOC_8_09_LSystemApp::prepareSettings( Settings *settings ) {
    settings->setWindowSize(600, 600);
}


void NOC_8_09_LSystemApp::mouseDown( MouseEvent event )
{
    mLSystem->generate();
//    std::cout << mLSystem->getSentence() << "\n\n" << std::endl; // debug: print out current sentence
    mTurtle->setTodo( mLSystem->getSentence() );
    mTurtle->changeLength(0.5);
    mTurtle->calculatePaths();
}

void NOC_8_09_LSystemApp::update()
{
}

void NOC_8_09_LSystemApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 1, 1, 1 ) );
    gl::color(0, 0, 0);
    mTurtle->draw();
}

CINDER_APP_NATIVE( NOC_8_09_LSystemApp, RendererGl )
