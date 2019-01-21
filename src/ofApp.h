#pragma once

#include "ofMain.h"
#include "ofWall.h"
#include "ofCar.h"
#include "ofxOpenCv.h"
#include "ofVideoPlayer.h"
#include "iostream"

using namespace std;

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void checkCollision();
    void changeCarDirection(string direction);

    void vid_setup();
    void vid_update(void);
    void vid_draw(void);

    uint8_t vid_opacity;
    int vid_h;
    int vid_w;
    bool vid_show_last_diff;
    int leftPixelsFilled;
    int rightPixelsFilled;
    bool gameover;
    uint64_t startJumpTime;
    uint64_t currentTime;
    uint64_t delayTime;

    bool isJumping;

    ofVideoGrabber vidGrabber;

    ofxCvColorImage			colorImg;
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    int         			threshold;
    bool            		bLearnBakground;

    ofSoundPlayer beat;
    ofSoundStream mic;
    void audioIn(float* input, int bufferSize, int nChannels);

    float *fftSmooth;
    int bands;

    vector <ofWall> wall;
    ofCar car;
};
