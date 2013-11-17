//
//  Turtle.cpp
//  NOC_8_09_LSystem
//
//  Created by Armin H. on 11/15/13.
//
//

#include "Turtle.h"


Turtle::Turtle( std::string todo, float length, float thetastep ) {
    mTodo = todo;
    mLength = length;
    mThetaStep = thetastep;
    mTheta = -M_PI_2;
    mStartpoint = ci::Vec2f( ci::app::getWindowWidth()/2, ci::app::getWindowHeight() );
    mCurrentPosition = mStartpoint;
    
    calculatePaths();
}

void Turtle::calculatePaths() {
    for (int i = 0; i < mSegments.size(); i++) {
        delete mSegments[i];
    }
    mSegments.clear();
    mCurrentPosition = mStartpoint;
    mTheta = -M_PI_2;
    for (int i = 0; i < mTodo.size(); i++ ) {
        
        switch (mTodo[i]) {
            case 'F':
                mLastPosition = mCurrentPosition;
                mCurrentPosition += ci::Vec2f (mLength * cosf( mTheta ),
                                               mLength * sinf( mTheta ) );
                mSegments.push_back( new Segment( mLastPosition, mCurrentPosition ) );
                // debug: print line currently drawn:
//                std::cout << "Line drawn (From " << mLastPosition.x << "/" << mLastPosition.y << " to " << mCurrentPosition.x << "/" << mCurrentPosition.y << std::endl;
                
                break;
            case 'G':
                mLastPosition = mCurrentPosition;
                mCurrentPosition += ci::Vec2f (mLength * cosf( mTheta ),
                                               mLength * sinf( mTheta ) );
                break;
            case '+':
                mTheta += mThetaStep;
//                std::cout << "theta + (theat = " << ci::toDegrees(mTheta) << ")"<< std::endl;
                break;
            case '-':
                mTheta -= mThetaStep;
//                std::cout << "theta - (theta = " << ci::toDegrees(mTheta)  << ")" << std::endl;
                break;
            case '[':
                mRestorePosition.push_back( mCurrentPosition )   ;
                mRestoreAngle.push_back( mTheta );
//                std::cout << "Saved: " << mCurrentPosition.x << " / " << mCurrentPosition.y << std::endl;
                break;
            case ']':
                mCurrentPosition = mRestorePosition.back();
                mTheta = mRestoreAngle.back();
//                std::cout << "Restored: " << mCurrentPosition.x << " / " << mCurrentPosition.y << std::endl;
                mRestorePosition.pop_back();
                mRestoreAngle.pop_back();
                break;                
            default:
                break;
        }
    }
}

void Turtle::draw() {
    for (auto s : mSegments ) {
        s->draw();
    }
}

void Turtle::setLength( float length ) { mLength = length; }

void Turtle::changeLength( float percent ) { mLength *= percent; }

void Turtle::setTodo( std::string todo ) { mTodo = todo; }




