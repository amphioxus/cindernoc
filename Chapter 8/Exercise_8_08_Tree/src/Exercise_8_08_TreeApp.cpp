/**
 The Nature of Code
 Daniel Shiffman
 
 Examples ported to Cinder ( http://libcinder.org )
 
 Armin J Hinterwirth (trying to learn C++ by playing with Cinder)
 
 Exercise 8-8: Object-oriented Recursive Tree
 
 */

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Tree.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Exercise_8_08_TreeApp : public AppNative {
    Tree * mTree;
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void Exercise_8_08_TreeApp::setup()
{
    mTree = new Tree();
}

void Exercise_8_08_TreeApp::mouseDown( MouseEvent event )
{
    mTree->resetTree();
//    std::cout << "Number of branches: " << mTree->getNoBranches() << std::endl;

}

void Exercise_8_08_TreeApp::update()
{
}

void Exercise_8_08_TreeApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    mTree->draw();
}

CINDER_APP_NATIVE( Exercise_8_08_TreeApp, RendererGl )
