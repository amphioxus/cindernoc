//
//  DNA.cpp
//  NOC_9_01_GA
//
//  Created by Armin H. on 11/20/13.
//
//

#include "DNA.h"



DNA::DNA( int num ) {
    // set up initial DNA chunk with random char sequence:
    
    ci::randSeed( clock() );
    for (int i=0; i < num; i++) {
        char c = (char) (ci::randInt(32,128)); // Pick from range of chars
//        char c = (char) (ci::randInt(65,90)); // Pick from range of chars
        
        mSequence.push_back( c ); // add it to the string container
    }

}

void DNA::setSequence( std::string seq ) {
    mSequence = seq;
}

std::string DNA::getSequence() {
    return mSequence;
}


void DNA::evalFitness( std::string target ) {
    // THE FITNESS FUNCTION
    int score = 0;
    if (mSequence.length() != target.length() ){
        std::cout << "Something odd is happening" << std::endl; // debug
    }
    for (int i=0; i < target.length(); i++ ) {
        if ( mSequence[i] == target[i] ) {
            score++;
        }
    }
    mFitness = (float) score / (float) target.length();

}


float DNA::getFitness() {
    return mFitness;
}


void DNA::crossover( const DNA *partner, DNA * child ) {
    int midpoint = ci::randInt( mSequence.length() );
    
    // Half from one, half from the other
    for (int i = 0; i < mSequence.length(); i++ ) {
        if (i > midpoint) {
            child->mSequence[i] = mSequence[i];
        } else {
            child->mSequence[i] = partner->mSequence[i];
        }
    }
}

// Based on a mutation probability, picks a new random character
void DNA::mutate( float mutationRate ) {
    // go through the genetic sequence:
    for (int i = 0; i < mSequence.length(); i++ ) {
        // With probabilty of mutationrate, change char at i:
        if (ci::randFloat() < mutationRate ) {
            mSequence[i] = (char) (ci::randInt(32,128));
        }
    }
}

DNA::~DNA() {
//    std::cout << "DNA destructor called" << std::endl; // debug
}


