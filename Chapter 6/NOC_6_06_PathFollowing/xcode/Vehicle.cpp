//
//  Vehicle.cpp
//  NOC_6_01_Seek
//
//  Created by Armin H. on 10/3/13.
//
//

#include "Vehicle.h"


Vehicle::Vehicle( ci::Vec2f location ) {
    mLocation = location;
    mVelocity = ci::Vec2f(0., 0.);
    mAcceleration = ci::Vec2f(0.,0.);
    mR = 6.;
    mMaxForce = .5;
    mMaxSpeed = 8.;
}


Vehicle::Vehicle( ci::Vec2f location, float maxSpeed, float maxForce ) {
    mLocation = location;
    mVelocity = ci::Vec2f(0,0);
    mAcceleration = ci::Vec2f(0,0);
    mR = 6.;
    mMaxForce = maxForce;
    mMaxSpeed = maxSpeed;
}


void Vehicle::update() {
    // remember location for history trail:
    mHistoryTrail.push_back( mLocation );
    if (mHistoryTrail.size() > mHistoryLength) {
        mHistoryTrail.pop_front();
    }

    // Update velocity
    mVelocity += mAcceleration;
    // Limit speed
    mVelocity.limit( mMaxSpeed );
    mLocation += mVelocity;
    // Reset accelerationelertion to 0 each cycle
    mAcceleration *= 0;
    
    // calculate heading:
    mTheta = atan2f(mVelocity.y, mVelocity.x);
}


// This function implements Craig Reynolds' path following algorithm
// http://www.red3d.com/cwr/steer/PathFollow.html

void Vehicle::follow( Path *path ) {
    
    // Predict location 25 (arbitrary choice) frames ahead
    mPredictedLoc = mLocation + mVelocity.normalized() * LOOK_AHEAD_DIST;

    // Now we must find the normal to the path from the predicted location
    // We look at the normal for each line segment and pick out the closest one
    
    // Loop through all points of the path
    float record2Beat = 10000000.;
    ci::Vec2f normal_temp;
    for (int i = 0; i < path->mVerts.size()-1; i++ ) {
        // Look at a line segment
        ci::Vec2f lineAB = (path->mVerts.at(i+1) - path->mVerts.at(i)).normalized();
        ci::Vec2f lineAP = mPredictedLoc - path->mVerts.at(i);
        
        normal_temp = path->mVerts.at(i) + lineAB * lineAP.dot( lineAB );
        
        if (normal_temp.x < path->mVerts.at(i).x || normal_temp.x > path->mVerts.at(i+1).x) {
            normal_temp = path->mVerts.at(i+1);
        }
        // How far away are we from the path?
        float distance = (mPredictedLoc - normal_temp).length();
        
        if (distance < record2Beat ) {
            record2Beat = distance;
            mNormalPoint = normal_temp;
            mTarget = normal_temp + lineAB * TARGET_DISTANCE;
        }
    }
    if (record2Beat > path->getRadius() ) {
        seek( mTarget );
        mSteering = true;
    } else
        mSteering = false;
}


void Vehicle::seek( ci::Vec2f target ) {
    // A method that calculates a steering force towards a target
    // STEER = DESIRED MINUS VELOCITY
    ci::Vec2f desired = target - mLocation;
    float d = desired.length();
    // Normalize desired and scale to maximum speed
    desired.safeNormalize();
    // IF closer than 100 pixels:
    if (d < 100) {
        
        // set magnitude according to how close we are:
        float m = ci::lmap<float>(d, 0, 100, 0, mMaxSpeed);
        desired *= m;
    } else
        desired *= mMaxSpeed;
    // Steering = Desired minus velocity
    ci::Vec2f steer = desired - mVelocity;
    steer.limit( mMaxForce );
    applyForce( steer );
}


void Vehicle::checkBoundaries(ci::Rectf boundary) {
    ci::Vec2f desired = ci::Vec2f(NULL, NULL);
    
    if (mLocation.x < boundary.x1) {
        desired = ci::Vec2f(mMaxSpeed, mVelocity.y);
    }
    else if (mLocation.x > boundary.x2) {
        desired = ci::Vec2f(-mMaxSpeed, mVelocity.y);
    }
    
    if (mLocation.y < boundary.y1) {
        desired = ci::Vec2f(mVelocity.x, mMaxSpeed);
    }
    else if (mLocation.y > boundary.y2) {
        desired = ci::Vec2f(mVelocity.x, -mMaxSpeed);
    }
    
    if (desired != ci::Vec2f(NULL,NULL)) {
        desired.safeNormalize();
        desired *= mMaxSpeed;
        // Steering = Desired minus velocity
        ci::Vec2f steer = desired - mVelocity;
        steer.limit( mMaxForce );
        applyForce( steer );
    }
}

void Vehicle::checkBorders() {
    if (mLocation.x < -mR) {
        mLocation.x = ci::app::getWindowWidth()+mR;
    } else if (mLocation.x > ci::app::getWindowWidth()+mR) {
        mLocation.x = -mR;
    }
}

void Vehicle::applyForce( ci::Vec2f force ) {
    mAcceleration += (force / mMass);
    
}


bool Vehicle::isDead() {
    int buffer = 400; // pixel buffer around screen to account for tail
    // check whether vehicle (and its tail) wanders outside the defined window borders
    if (mLocation.x + buffer < 0 || mLocation.x - buffer > WINDOW_WIDTH) {
        return true;
    }
    else if (mLocation.y + buffer < 0 || mLocation.y - buffer > WINDOW_HEIGHT) {
        return true;
    } else
        return false;
}


void Vehicle::draw() {
    ci::gl::enableAlphaBlending();
    ci::gl::pushMatrices();
    
    ci::gl::translate( mLocation );
    ci::gl::rotate( ci::toDegrees(mTheta)+90 );
    ci::gl::color(.8, .4, .4);
    ci::gl::begin( GL_POLYGON );
    ci::gl::vertex( ci::Vec2f(0, -mR*2) );
    ci::gl::vertex( ci::Vec2f(-mR, mR*2) );
    ci::gl::vertex( ci::Vec2f(mR, mR*2) );
    ci::gl::end();
    ci::gl::color(.8, .8, .8);
    ci::gl::lineWidth(2.0);
    ci::gl::begin( GL_LINE_LOOP );
    ci::gl::vertex( ci::Vec2f(0, -mR*2) );
    ci::gl::vertex( ci::Vec2f(-mR, mR*2) );
    ci::gl::vertex( ci::Vec2f(mR, mR*2) );
    ci::gl::end();
    ci::gl::popMatrices();
    ci::gl::disableAlphaBlending();
}

void Vehicle::drawDebug()
{
    ci::gl::enableAlphaBlending();
    
//    ci::gl::color(0, .8, 0, .6);
    ci::gl::color(0, 0, 0);
    ci::gl::drawSolidCircle(mNormalPoint, 3.);
    if (mSteering) {
        ci::gl::color(1, 0, 0);
    }
    ci::gl::drawSolidCircle(mTarget, 4.);
    ci::gl::color(0, 0, 0);
    ci::gl::drawLine(mLocation, mPredictedLoc);
    ci::gl::drawLine(mPredictedLoc, mNormalPoint);
    ci::gl::drawSolidCircle(mPredictedLoc, 3.);
//    std::cout << mNormalPoint << std::endl;
    ci::gl::disableAlphaBlending();
}

void Vehicle::drawHistory() {
    ci::gl::enableAlphaBlending();
    glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    glPointSize(5);
    ci::gl::begin(GL_POINTS);
    for (int i = 0; i < mHistoryTrail.size(); ++i) {
        float alpha = ci::lmap<float>(i, 0, 255, 0.2, 1.0);
        ci::gl::color(1., .2, .2, alpha);
        ci::gl::vertex(mHistoryTrail.at(i));
    }
    ci::gl::end();
    ci::gl::disableAlphaBlending();
}

