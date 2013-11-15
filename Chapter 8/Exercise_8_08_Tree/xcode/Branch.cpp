//
//  Branch.cpp
//  NOC_8_07_TreeStochastic
//
//  Created by Armin H. on 11/14/13.
//
//

#include "Branch.h"


Branch::Branch( Vec2f start, Vec2f end, int bLevel ) {
    mStartP = start;
    mEndP = end;
    mLength = (mEndP-mStartP).length();
    mTheta = atan2f((mEndP-mStartP).y, (mEndP-mStartP).x);
    mHierarchy = bLevel;
}

Branch* Branch::branch( float angle ) {
    
    Vec2f branchvec = mEndP + Vec2f ( (mLength * mLredux) * cosf( mTheta + toRadians( angle ) ),
                                       (mLength * mLredux) * sinf( mTheta + toRadians( angle ) )  );
    
    return new Branch( mEndP, branchvec, mHierarchy+1 );
}

int Branch::getHierarchy() {
    return mHierarchy;
}

void Branch::draw() {
    gl::color(1, 0, 0);
    gl::drawLine( mStartP, mEndP );
}


Branch::~Branch() {
//    std::cout << "Branch destructor called" << std::endl; // debug
}