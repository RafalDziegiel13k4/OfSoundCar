#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    beat.load("music.flac");
    fftSmooth = new float [192];
    for (int i = 0; i < 192; i++)
    {
        fftSmooth[i] = 0;
    }

    bands = 2;

    beat.setLoop(true);
    beat.setVolume(0.2);

    ofSoundStreamListDevices();
    mic.setup(this, 0, 2, 44100, 256, 4);

    //ofBackground(205,133,63);
    vid_setup();
    beat.play();

    isJumping = false;
}

//--------------------------------------------------------------
void ofApp::update()
{
    currentTime = ofGetElapsedTimeMillis();

        //ofSoundUpdate();
        rightPixelsFilled = 0;
        leftPixelsFilled = 0;

        vid_update();

        if(!gameover && currentTime > 5000)
        {
            if(leftPixelsFilled - rightPixelsFilled > 20)
            {
                delayTime = currentTime;
                changeCarDirection("LEFT");
            }
            else if(rightPixelsFilled - leftPixelsFilled > 20)
            {
                delayTime = currentTime;
                changeCarDirection("RIGHT");
            }
            else if(currentTime - delayTime > 250)
            {
                changeCarDirection("UP");
            }

            float *value = ofSoundGetSpectrum(bands);
            fftSmooth[0]*=0.9f;

            if(fftSmooth[0] < value[0])
            {
                fftSmooth[0] = value[0];
            }

            for (int i = 0; i < wall.size(); i++)
            {
                wall[i].update();
                if(wall[i].y > ofGetHeight() + (wall[i].h * 2)) wall.erase(wall.begin() + i);
            }

            car.update();

            checkCollision();

            if(currentTime - startJumpTime > 800 && car.carDir == "JUMP")
            {
                car.carDir = "";
                changeCarDirection("UP");
            }
            else if(currentTime - startJumpTime > 300 && car.carDir == "JUMP")
            {
                isJumping = false;
            }
        }
}

//--------------------------------------------------------------
void ofApp::draw()
{
        ofSetColor(0);
        vid_draw();

        int length = fftSmooth[0] * 600;

        if(length > 0)
        {
            if(length > 255)
            {
                wall.push_back(ofWall(500));
                length = 255;
            }
            else
            {
                wall.push_back(ofWall(length));
            }

            car.color_val = length;
        }

        ofSetColor(205,133,63);
        ofDrawRectangle(400,0,ofGetWidth() - 400 * 2, ofGetHeight());

        for (int i = 0; i < wall.size(); i++)
        {
            wall[i].draw();
        }

        car.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch(key)
    {
    case OF_KEY_LEFT:
        threshold++;
        break;
    case OF_KEY_RIGHT:
        threshold--;
        break;
    case '1':
        beat.play();
        break;
    case '2':
        beat.stop();
        break;
    case ' ':
        gameover = false;
        isJumping = false;
        car.x = ofGetWidth() / 2;
        changeCarDirection("UP");
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch(key)
    {
    case OF_KEY_LEFT:
    case OF_KEY_RIGHT:
        car.carDir = "";
        changeCarDirection("UP");
        break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if(!isJumping)
    {
        if(x > car.x - car.scale_x/2 && x < car.x + car.scale_x/2)
        {
            if(y > car.y - car.scale_y/2 && y < car.y + car.scale_y/2)
            {
                if(car.carDir == "UP" || car.carDir == "JUMP")
                {
                    isJumping = true;
                    car.carDir = "";
                    currentTime = ofGetElapsedTimeMillis();
                    changeCarDirection("JUMP");
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::changeCarDirection(string direction)
{
    if(!gameover && car.carDir != "JUMP")
    {
        if(direction == "LEFT" && car.carDir != "LEFT")
        {
                car.scale_x = 82;
                car.scale_y = 80;
                car.car_img.load("car-left.png");
                car.position = -2;
                car.carDir = "LEFT";
        }
        else if(direction == "RIGHT" && car.carDir != "RIGHT")
        {
                car.scale_x = 82;
                car.scale_y = 80;
                car.car_img.load("car-right.png");
                car.position = 2;
                car.carDir = "RIGHT";
        }
        else if(direction == "UP" && car.carDir != "UP")
        {
                car.scale_x = 50;
                car.scale_y = 80;
                car.car_img.load("car-top.png");
                car.position = 0;
                car.carDir = "UP";
        }
        else if(direction == "JUMP" && car.carDir != "JUMP")
        {
                car.carDir = "JUMP";
                car.scale_x = 75;
                car.scale_y = 120;
                startJumpTime = ofGetElapsedTimeMillis();
                car.car_img.load("car-top.png");
                car.position = 0;
        }
    }
}

void ofApp::checkCollision()
{
    if(car.carDir != "JUMP")
    {
        for (int i = 0; i < wall.size(); i++)
        {
            if(wall[i].x1 + wall[i].w > car.x - (car.scale_x / 4) || wall[i].x2 - wall[i].w < car.x + (car.scale_x / 4))
            {
                if(wall[i].y > car.y - (car.scale_y / 2) && wall[i].y < car.y + (car.scale_y / 2))
                {
                    gameover = true;
                }
            }
        }
    }
}

void ofApp::vid_setup()
{
    vid_opacity = 100;
    vid_show_last_diff = true;

    vidGrabber.setDeviceID(0);
    vidGrabber.setVerbose(true);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.setup(640, 480);

    colorImg.allocate(640, 480);
    grayImage.allocate(640, 480);
    grayBg.allocate(640, 480);
    grayDiff.allocate(640, 480);

    threshold = 40;
}

void ofApp::vid_update(void)
{
    unsigned char* pixelData;

    vid_w = ofGetWidth();
    vid_h = ofGetHeight();

    ofBackground(100, 100, 100);

    bool bNewFrame = false;

    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();

    if(bNewFrame)
    {
        colorImg.setFromPixels(vidGrabber.getPixels());
        colorImg.mirror(false, true);

        grayImage = colorImg;

        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        grayBg = grayImage;

        pixelData = grayDiff.getPixels().getData();

        int arrayIndex1 = 0;
        int arrayIndex2 = 0;

        for(int k = 0; k <= ofGetHeight(); k++)
        {
            for(int l = 0; l <= 160; l++)
            {
                arrayIndex1 = grayDiff.getPixels().getPixelIndex(l, k);

                if(pixelData[arrayIndex1] == 255)
                {
                    leftPixelsFilled++;
                }
            }

            for(int l = 480; l <= 640; l++)
            {
                arrayIndex2 = grayDiff.getPixels().getPixelIndex(l, k);

                if(pixelData[arrayIndex2] == 255)
                {
                    rightPixelsFilled++;
                }
            }
        }
    }
}

void ofApp::vid_draw(void)
{
    colorImg.draw(0, 0, ofGetWidth(),ofGetHeight());
    if(vid_show_last_diff == true)
    {
        ofSetColor(255, 255, 255, vid_opacity);
        grayDiff.draw(0, 0, ofGetWidth(),ofGetHeight());
    }
    ofSetColor(255, 255, 255, 255);
}

void ofApp::audioIn(float* input, int bufferSize, int nChannels)
{
    int micVal = abs(input[0]);

    if(micVal >= 1 && isJumping == false)
    {
        if(car.carDir == "UP" || car.carDir == "JUMP")
        {
            isJumping = true;
            car.carDir = "";
            currentTime = ofGetElapsedTimeMillis();
            changeCarDirection("JUMP");
            cout << "MIC SIGNAL!" << endl;
        }
    }
}
