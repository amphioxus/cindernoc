//
//  Rule.cpp
//  NOC_8_09_LSystem
//
//  Created by Armin H. on 11/15/13.
//
//

#include "Rule.h"


Rule::Rule( char a, std::string b ) {
    mA = a;
    mB = b;
}

char Rule::getA() { return mA; }

std::string Rule::getB() { return mB; }

