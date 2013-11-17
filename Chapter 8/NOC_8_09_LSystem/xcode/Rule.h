//
//  Rule.h
//  NOC_8_09_LSystem
//
//  Created by Armin H. on 11/15/13.
//
//

/*  A Class to describe an
 *  LSystem Rule
*/

#pragma once
#include <iostream>


class Rule {
protected:
    char mA;
    std::string mB;
public:
    Rule( char a, std::string b );
    char getA();
    std::string getB();
};


