//
//  DNA.h
//  NOC_9_01_GA
//
//  Created by Armin H. on 11/20/13.
//
//

#pragma once
#include <iostream>
#include "cinder/Rand.h"
#include <ctime>
#include <string>

class DNA {
    std::string mSequence; // The genetic sequence
    float mFitness;
public:
    DNA(int num);
    ~DNA();
    
    // methods to get and set the genetic sequence for this DNA
    std::string getSequence();
    void setSequence( std::string );
    // methods to calculate fitness and get fitness value
    void evalFitness( std::string target );
    float getFitness();
    void crossover( const DNA *partner, DNA * child );
    void mutate( float mutationRate );
};
