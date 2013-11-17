//
//  LSystem.h
//  NOC_8_09_LSystem
//
//  Created by Armin H. on 11/15/13.
//
//

#pragma once
#include <iostream>
#include "Rule.h"

class LSystem {
protected:
    std::string mSentence;  // The sentence (a String)
    std::vector< Rule > mRuleset; // The ruleset (an array of Rule objects)
    int mGeneration; // Keeping track of the generation #
public:
    LSystem( std::string axiom, std::vector< Rule > );
    
    void generate();
    std::string getSentence();
    int getGeneration();
    
};