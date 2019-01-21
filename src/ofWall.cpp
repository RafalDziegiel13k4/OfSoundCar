#include "ofWall.h"

ofWall::ofWall(float _w)
{
    w = _w;
    h = 8;
    x1 = 400;
    x2 = ofGetWidth() - 400;
    y = 0;

    //color.set(ofRandom(255),ofRandom(255),ofRandom(255));
    color.set(34,139,34);
}

void ofWall::update()
{
    y = y + h;
}

void ofWall::draw()
{
    ofSetColor(color);
    ofDrawRectangle(x1, y, w, h);
    ofDrawRectangle(x2, y, (-1 * w), h);
}
