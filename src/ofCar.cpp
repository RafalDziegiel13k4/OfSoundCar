#include "ofCar.h"

ofCar::ofCar()
{
    car_img.load("car-top.png");
    x = ofGetWidth() / 2;
    position = 0;
    y = ofGetHeight() - 100;
    color_val = 0;

    scale_x = 50;
    scale_y = 80;
}

void ofCar::update()
{
    if(position > 0)
    {
        if(x < ofGetWidth() - 400 - scale_x/2) x = x + position;
    }
    else if(position < 0)
    {
        if(x > 480 - scale_x/2) x = x + position;
    }

    color_val = color_val;
}

void ofCar::draw()
{
    if(carDir == "JUMP")
    {
        ofSetColor(0,0,0,128);
        ofDrawCircle(x,y,50);
    }

    ofSetColor(color_val,20,40);
    car_img.setAnchorPercent(0.5, 0.5);
    car_img.draw(x,y,scale_x,scale_y);
}
