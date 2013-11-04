//
//  GOL.h
//  NOC_7_02_GameOfLifeOOP
//
//  Created by Armin H. on 10/31/13.
//
//

#pragma once
#include <iostream>
#include "Cell.h"

class GOL {
public:
    GOL();
    
    std::vector< std::vector < Cell * > > mBoard;
    int mW = 10;
    int mColumns, mRows;
    
    void init();
    void resize();
    void reset();
    void giveBirth( ci::Vec2f );
    void generate();
    void draw();
    
    ~GOL();
};