//
//  FlowField.cpp
//  NOC_6_04_Flowfield
//
//  Created by Armin H. on 10/4/13.
//
//

#include "FlowField.h"


FlowField::FlowField( int resolution ) {
    
    mPerlin = new ci::Perlin();
    
    mResolution = resolution;
    mArrowSize = resolution/10;
    init();
}


void FlowField::init() {
    mPerlin->setSeed( ci::randInt() );
    mCols = ci::app::getWindowWidth() / mResolution;
    mRows = ci::app::getWindowHeight() / mResolution;
    if ( !mFlowField.empty() ) {
        mFlowField.clear();
    }
    // Set up 2D vector sizes. (HEIGHT x WIDTH)
    // See http://www.cplusplus.com/forum/articles/7459/
    // for info on multidimensional arrays in C++
    mFlowField.resize(mRows);
    for (int i = 0; i < mRows; ++i) {
        mFlowField[i].resize(mCols);
    }

    // go through 2D array.
    for (int c = 0;  c < mCols; ++c) {
        // for each column, go through all rows:
        for (int r = 0; r < mRows; ++r) {
            // make location vector for calculating Perlin noise
            ci::Vec2f loc = ci::Vec2f( c * mResolution,
                                       r * mResolution);
            // create the Perlin noise from the current location vector:
            float noise = mPerlin->fBm( ci::Vec3f( loc * 0.005f, ci::app::getElapsedSeconds() * 0.2f ) );
            // multiply this noise, because otherwise there's a tendency for all vectors to point to the right
            float noiseMultiplier = 10.f;
            noise *= noiseMultiplier;
            // create Perlin noise direction (polar coordinates) for this location:
            mFlowField[r][c] = ci::Vec2f( ci::math<float>::cos( noise ),
                                          ci::math<float>::sin( noise ) );
        }
    }
}


ci::Vec2f FlowField::lookup( ci::Vec2f loc )
{
    int row = ci::math<float>::clamp(loc.y/mResolution, 0, mRows-1);
    int col = ci::math<float>::clamp(loc.x/mResolution, 0, mCols-1);
    
    return mFlowField[row][col];
}


void FlowField::drawVector( ci::Vec2f vec, ci::Vec2f loc )
{
    // Quickly implemented method that does lots of pushing and popping.
    // Probably better to draw everything in one go eventually.
    
    float heading = ci::math<float>::atan2(vec.y, vec.x);
    
    ci::gl::pushMatrices();
    ci::gl::translate( loc );
    ci::gl::rotate( ci::toDegrees( heading )  );
    // Calculate length of vector & scale it to be bigger or smaller if necessary
    float length = vec.length() * 3*mResolution/4;
    ci::gl::lineWidth(1.0);
    ci::gl::color(.3, .3, .5, .2);
    ci::gl::drawLine( ci::Vec2f (-length/2, 0.0), ci::Vec2f (length/2, 0.0 ));
    ci::gl::drawLine( ci::Vec2f (length/2, 0.0 ), ci::Vec2f (length/2-mArrowSize, mArrowSize/2) );
    ci::gl::drawLine( ci::Vec2f (length/2, 0.0 ), ci::Vec2f (length/2-mArrowSize, -mArrowSize/2) );
//
    ci::gl::popMatrices();
}


void FlowField::drawGrid() {
    ci::gl::begin(GL_LINES);
    ci::gl::lineWidth(1.0);
    ci::gl::color(.4, .2, 0, .2);
    for (int c = 0; c <= mCols; c++) {
        ci::gl::vertex( ci::Vec2f( c * mResolution,
                                  0) );
        ci::gl::vertex( ci::Vec2f( c * mResolution,
                                   WINDOW_HEIGHT ) );
    }
    
    for (int r = 0; r <= mRows; r++) {
        ci::gl::vertex( ci::Vec2f( 0,
                                   r * mResolution) );
        ci::gl::vertex( ci::Vec2f( WINDOW_WIDTH,
                                   r * mResolution) );
    }
    ci::gl::end();
}


void FlowField::draw() {
    for (int c = 0; c < mCols; ++c) {
        for (int r = 0; r < mRows; ++r) {
            drawVector(mFlowField[r][c], ci::Vec2f( mResolution/2 + c * mResolution,
                                                    mResolution/2 + r * mResolution));
        }
    }
}



