//
//  Tree.h
//  NOC_8_07_TreeStochastic
//
//  Created by Armin H. on 11/14/13.
//
//

#pragma once
#include <iostream>
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "Branch.h"

using namespace ci;

class Tree {
protected:
    std::vector< Branch *> mBranches;
    int mTreeSize = 3000; // max number of branches
    int mNumber;
    int mCurrentLevel; 
public:
    Tree();
    Tree( Vec2f startloc, float initLength );
    ~Tree();
    
    void createTree();
    void clearTree();
    int getNoBranches();
    void branch();
    void draw();
};