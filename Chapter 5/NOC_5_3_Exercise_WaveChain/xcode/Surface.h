//
//  Surface.h
//  NOC_5_3_Exercise_WaveChain
//
//  Created by Armin H. on 9/24/13.
//
//

#pragma once
#include <iostream>
#include "Box2d.h"
#include "Scale.h"

namespace box2d
{

class Surface {
    std::vector<ci::Vec2f> mSurfaceVerts;
    
public:
    Surface( std::vector<ci::Vec2f> surface, b2World &world); // constructor for vertex list supplied as cinder vector vector
    b2World *mWorld;
    b2Body *mBody;
    box2d::Scale scale;
    
    void update();
    void draw();
};

}