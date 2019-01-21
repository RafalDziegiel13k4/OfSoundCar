#ifndef _OF_WALL    // by using this if statement you prevent the class to be called more than once - in other words what we're saying here is
#define _OF_WALL    //if the class has NOT been defined then define it

#include "ofMain.h"

class ofWall
{

public:
  void update();
  void draw();

  //constructor
  ofWall(float w);
  
  // variables
  float x1, y, x2, w, h;
  int dim, lives;
  float speedX;
  float speedY;

  ofColor color;
  
private:

};

#endif 
