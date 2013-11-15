//
//  Tree.cpp
//  NOC_8_07_TreeStochastic
//
//  Created by Armin H. on 11/14/13.
//
//

#include "Tree.h"

// constructor:
Tree::Tree() {
    mCurrentLevel = 0; // we are at zeroeth order of branching at this point
    Vec2f startloc = Vec2f( app::getWindowWidth()/2 , app::getWindowHeight()-10 );
    mBranches.push_back( new Branch( startloc,
                                     startloc + Vec2f( 0, -app::getWindowHeight()/3),
                                     mCurrentLevel )
                        );
    mNumber = 1; // keep track of number of branches
    createTree();
}


// constructor with initial settings:
Tree::Tree( Vec2f startloc, float initLength ) {
    mCurrentLevel = 0; // we are at zeroeth order of branching at this point
    mBranches.push_back( new Branch( startloc,
                                     startloc + Vec2f( 0, -initLength),
                                     mCurrentLevel )
                        );
    mNumber = 1; // keep track of number of branches
    createTree();
    
}

void Tree::createTree() {
    // create not too many more branches than mTreeSize. (If it's a large number,
    // the actual branch number could be substantially larger than mTreeSize, though.)
    while ( mNumber < mTreeSize ) {
        branch();
    }
}

void Tree::clearTree() {
    // delete the branch objects:
    for (auto b : mBranches ) {
        delete b;
    }
    // clear the container:
    mBranches.clear();
    // set up for new start:
    mNumber = 0;
    mCurrentLevel = 0;
    // create first branch:
    Vec2f startloc = Vec2f( app::getWindowWidth()/2 , app::getWindowHeight()-10 );
    mBranches.push_back( new Branch( startloc,
                                    startloc + Vec2f( 0, -app::getWindowHeight()/3),
                                    mCurrentLevel )
                        );
}

void Tree::branch() {
    std::vector< Branch * > subB;
    
    for (auto b : mBranches ) {
        // only branch the newest branches:
        if (b->getHierarchy() == mCurrentLevel ) {
            subB.push_back( b->branch( randFloat(0.f, 60.f) ));
            subB.push_back( b->branch( randFloat(0.f, -60.f) ));
            mNumber += 2;
        }
    }
    // add new points to our branch collecting container:
    mBranches.insert(mBranches.end(), subB.begin(), subB.end() );
    mCurrentLevel++; // increment branching level
}

// return number of branches:
int Tree::getNoBranches() {   return mNumber;  }

void Tree::draw() {
    // draw each branch:
    for (auto b : mBranches ) {
        b->draw();
    }
}