//
//  Population.h
//  NOC_9_01_GA
//
//  Created by Armin H. on 11/20/13.
//
//

#pragma once
#include <iostream>
#include <sstream>
#include "cinder/CinderMath.h"
#include "DNA.h"


class Population {
    std::string mTarget;
    float mMutationRate;                // Mutation rate
    std::vector<DNA *> mPopulation;     // Array to hold the current population
    std::vector<DNA *> mMatingPool;     // holds the "mating pool"
    int mGenerations;                   // Number of generations
    bool mFinished;                     // Are we finished evolving?
    int mPerfectScore;                  // the score at which we are finished
    int mPopulationSize;
    float mMaxFitness;                  // the fitness score of the fittest 

    
public:
    Population( std::string targetString, float mutationRate, int populationSize );
    
    void calculateFitness();        // evaluate fitness for all DNA members of this population
    void applyNaturalSelection();   // create the mating pool
    void generate();                // generate the next generation (mating pool goes at it)
    
    int getGenerations();           // return number of generations
    std::string getBest();          // return best phrase
    void findFittest();             // find the fittest of them all
    float getFittest();             // return the fitness of the best member
    std::string getAllSequences();  // return sequences of all DNA chunks in population
    bool isFinished();
    float getAverageFitness();
    void resetPopulation();         // reset to random initial state and generation 0
    
    std::string getInfo();          // debugging info
};
