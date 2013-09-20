//
//  Confetti.cpp
//  NOC_4_05_ParticleSystemInheritancePolymorphism
//
//  Created by Armin H. on 9/19/13.
//
//

#include "Confetti.h"

Confetti::Confetti( ci::Vec2f location ) : Particle( location ) {
    
}

void Confetti::draw() {
    float alpha = ci::lmap<float>(mLifeSpan, 0, 255, 0, 1);
    float ww = ci::app::getWindowWidth();
    float theta = ci::lmap<float>( mLocation.x , 0, ww, 0, ww/10*M_2_PI);
    
//    std::cout << mLocation.x << std::endl;
    
    ci::Rectf rect (-5, 5, 5, -5);
    ci::gl::enableAlphaBlending();
    ci::gl::pushMatrices();
    
    ci::gl::translate( mLocation );
    ci::gl::rotate( ci::toDegrees( theta ) );
    ci::gl::color(.4, .8, .4, alpha);
    ci::gl::drawSolidRect( rect );
//    ci::gl::drawSolidCircle( ci::Vec2f(0.,0.) , 2.0);
    ci::gl::popMatrices();
    ci::gl::disableAlphaBlending();
}

