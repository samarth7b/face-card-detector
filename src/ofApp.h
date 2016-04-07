#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber cam;
    ofxCv::ObjectFinder finder;
    
    void scan_dir_imgs(ofDirectory dir);
    
    ofxCvColorImage img;
    ofxCvGrayscaleImage imageToExamine;
    ofImage fileImage;
    
    ofFile imageFile;
    
    ofRectangle clippingMask;
};
