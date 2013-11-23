//
//  Population.cpp
//  NOC_9_01_GA
//
//  Created by Armin H. on 11/20/13.
//
//

#include "Population.h"


Population::Population( std::string targetString, float mutationRate, int populationSize ) {
    mTarget = targetString;
    mMutationRate = mutationRate;
    mPopulationSize = populationSize;
    mGenerations = 0;
    mFinished = false;
    for (int i = 0; i < populationSize; i++ ) {
        mPopulation.push_back( new DNA( targetString.length() ) );
    }
    calculateFitness(); // calculates fitness value for the newly created DNA

//    mPerfectScore = (int) powf(2, targetString.length() );
    mPerfectScore = 1;
}


void Population::calculateFitness() {
    // Calculate a fitness value for every member of the population
    for (int i = 0; i < mPopulation.size(); i++ ) {
        mPopulation[i]->evalFitness( mTarget );
    }
}


void Population::applyNaturalSelection() {
    mMatingPool.clear(); // clear the pool before filling it up
    
    // find the fittest in the population (updates mMaxFitness member variable):
    findFittest();

    // Based on fitness, each member will get added to the mating pool a certain number of times
    // a higher fitness = more entries to mating pool = more likely to be picked as a parent
    // a lower fitness = fewer entries to mating pool = less likely to be picked as a parent
    for (int i = 0; i < mPopulation.size(); i++) {
        // map the range of fitness values to between 0 and 1:
        float fitness = ci::lmap<float>(mPopulation[i]->getFitness(), 0, mMaxFitness, 0, 1);
        int n = int(fitness * 100);  // Arbitrary multiplier, we can also use monte carlo method
        for (int j = 0; j < n; j++ ) {
            mMatingPool.push_back( mPopulation[i] ); // only pointers are added! No new object instances are created.
        }
    }
}

void Population::generate() {
    // Refill the population with children from the mating pool.
    // Go through each member of the population:
    for (int i = 0; i < mPopulation.size(); i++ ) {
        int a = ci::randInt( mMatingPool.size()-1 );
        int b = ci::randInt( mMatingPool.size()-1 );
        
        DNA * partnerA = mMatingPool[a];  // pointer to partner A, randomly chosen from mating pool
        DNA * partnerB = mMatingPool[b];  // pointer to partner B, randomly chosen from mating pool
        
        DNA * child = new DNA( mTarget.length() );  // pointer to new baby DNA
        partnerA->crossover( partnerB, child );     // baby DNA gets information from both parents

        child->mutate( mMutationRate );  // no baby is perfect: mutation!

        mPopulation[i] = child;
    }
    mGenerations++;
}


void Population::findFittest() {
    // find the fittest in the population:
    float maxFitness = 0.;
    for (int i = 0; i < mPopulation.size(); i++ ) {
        if (mPopulation[i]->getFitness() > maxFitness ) {
            maxFitness = mPopulation[i]->getFitness();
        }
    }
    mMaxFitness = maxFitness;
}


float Population::getFittest() {
    return mMaxFitness;
}

std::string Population::getAllSequences() {
    std::ostringstream ss;
    int displaylimit = MIN(mPopulation.size(), 40);
    
    for (int i = 0; i < displaylimit; i++ ) {
        ss << mPopulation[i]->getSequence() << "\n";
    }
    std::string everything( ss.str() );
    return everything;
}


int Population::getGenerations() {
    return mGenerations;
}


std::string Population::getBest() {
    float record = 0.f;
    int index = 0;
    for (int i = 0; i < mPopulation.size(); i++ ) {
        if (mPopulation[i]->getFitness() > record ) {
            index = i;
            record = mPopulation[i]->getFitness();
        }
    }
    
    if ( record == mPerfectScore ) {
        mFinished = true;
    }
    return mPopulation[index]->getSequence();
}


bool Population::isFinished() { return mFinished; }


// Compute average fitness for the population
float Population::getAverageFitness() {
    float total = 0.;
    for (int i = 0; i < mPopulation.size(); i++ ) {
        total += mPopulation[i]->getFitness();
    }
    return total / mPopulation.size();
}


void Population::resetPopulation() {
    mPopulation.clear();
    mGenerations = 0;
    mFinished = false;
    
    for (int i = 0; i < mPopulationSize; i++ ) {
        mPopulation.push_back( new DNA( mTarget.length() ) );
    }
    calculateFitness(); // calculates fitness value for the newly created DNA
    findFittest();
}

std::string Population::getInfo() {
    std::ostringstream ss;
    ss << "\n sequ.\tfit\n------------------\n";
    int displaylimit = MIN(mPopulation.size(), 50);
    
    for (int i = 0; i < displaylimit; i++ ) {
        ss << mPopulation[i]->getSequence() + "\t";
        
        ss << mPopulation[i]->getFitness();
        ss << "\n";
    }
    
    ss << "Average fitness: " << getAverageFitness();
    ss << "\n";
    std::string everything( ss.str() );
    return everything;
}