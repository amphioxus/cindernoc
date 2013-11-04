//
//  GOL.cpp
//  NOC_7_02_GameOfLifeOOP
//
//  Created by Armin H. on 10/31/13.
//
//

#include "GOL.h"


GOL::GOL() {
    init();
}

void GOL::init() {
    mColumns = ci::app::getWindowWidth() / mW;
    mRows = ci::app::getWindowHeight() / mW;
    
    // set up 2D board dimensions for std::vector:
    mBoard.resize( mRows );
    for (int r = 0; r < mRows; r++ ) {
        mBoard[r].resize( mColumns );
    }
    
    // go through each board cell and initialize Cell object:
    for (int c = 0;  c < mColumns; c++) {
        for (int r = 0; r < mRows; r++) {
            mBoard[r][c] = new Cell(c * mW, r * mW, mW);
        }
    }
}


void GOL::resize() {
    mW = ci::app::getWindowWidth() / mColumns;
    mW = ci::app::getWindowHeight() / mRows;
    // go through each board cell and resize Cell object:
    for (int c = 0;  c < mColumns; c++) {
        for (int r = 0; r < mRows; r++) {
            mBoard[r][c]->updateDims(c * mW, r * mW, mW);
        }
    }
}


void GOL::reset() {
       for (int c = 0;  c < mColumns; c++) {
        for (int r = 0; r < mRows; r++) {
            mBoard[r][c]->reset();
        }
    }
}


void GOL::giveBirth( ci::Vec2f mloc ) {
    // find cell index from location:
    int c = mloc.x / mW;
    int r = mloc.y / mW;
    
    mBoard[r][c]->newstate(1);
    
}


void GOL::generate() {
    // go through each cell on board and save state:
    for (int c = 0; c < mColumns; c++) {
        for (int r = 0; r < mRows; r++) {
            mBoard[r][c]->savePrevious();
        }
    }
    
    
    // Loop through every spot in our 2D array and check spots neighbors
    for (int c = 0; c < mColumns; c++) {
        for (int r = 0; r < mRows; r++) {
            int neighbors = 0;
            // Add up all the states in a 3x3 surrounding grid
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    neighbors += mBoard[(r + j + mRows)%mRows][(c + i + mColumns)%mColumns]->mStatePrevious;
                }
            }
            // A little trick to subtract the current cell's state since
            // we added it in the above loop
            neighbors -= mBoard[r][c]->mStatePrevious;
     
            // Rules of Life
            
            if (  mBoard[r][c]->mStateCurrent == 1 && neighbors < 2 ) {
                mBoard[r][c]->newstate(0);  // Loneliness
            }
            else if ( mBoard[r][c]->mStateCurrent == 1 && neighbors > 3 ) {
                mBoard[r][c]->newstate(0); // Overpopulation
            }
            else if ( mBoard[r][c]->mStateCurrent == 0 && neighbors == 3 ) {
                mBoard[r][c]->newstate(1); // Reproduction
            }
            // else do nothing!
        }
    }
}


void GOL::draw() {
    for (int c = 0; c < mColumns; c++) {
        for (int r = 0; r < mRows; r++) {
            mBoard[r][c]->draw();
        }
    }
}


GOL::~GOL() {
    for (int c = 0; c < mColumns; c++) {
        for (int r = 0; r < mRows; r++) {
            delete mBoard[r][c];
        }
    }
}