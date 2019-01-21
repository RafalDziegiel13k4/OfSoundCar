#ifndef _OF_CAR    // by using this if statement you prevent the class to be called more than once - in other words what we're saying here is
#define _OF_CAR    //if the class has NOT been defined then define it

#include "ofMain.h"

class ofCar
{

public:
  void update();
  void draw();

  //constructor
  ofCar();
  
  // variables
  float x, y, position, color_val;
  float scale_x, scale_y;
  string carDir;

  ofColor color;
  ofImage car_img;
  
private:

};

#endif 
