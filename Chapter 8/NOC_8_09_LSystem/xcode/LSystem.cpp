//
//  LSystem.cpp
//  NOC_8_09_LSystem
//
//  Created by Armin H. on 11/15/13.
//
//

#include "LSystem.h"


LSystem::LSystem( std::string axiom, std::vector< Rule > r) {
    mRuleset = r;
    mSentence = axiom;
    mGeneration = 0;
}


void LSystem::generate() {
    std::string nextgen;
    
    for (int i = 0; i < mSentence.length(); i++) {
        char &currChar = mSentence[i];
        std::string replace;
        
        // Check every rule
        for (int j=0; j < mRuleset.size(); j++) {
            char a = mRuleset[j].getA();
            // if we match the Rule, get the replacement String out of the Rule
            if (currChar == a) {
                replace = mRuleset[j].getB();
                break;
            } else {
                replace = currChar;
            }
        }
        // Append replacement String
        nextgen.append(replace);
    }
    mSentence.clear();
    mSentence = nextgen;
    mGeneration++;
}


int LSystem::getGeneration() { return mGeneration; }


std::string LSystem::getSentence() { return mSentence; }