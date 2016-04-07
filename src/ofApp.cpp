#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::scan_dir_imgs(ofDirectory dir){
    int size = dir.listDir();
    
    ofImage temp;
    int face_count = 0;
    
    for(int i = 0; i < size; i++){
        imageFile = dir.getFile(i);
        fileImage.load(imageFile);
        img.setFromPixels(fileImage.getPixels());
        imageToExamine = img;
        
        finder.update(imageToExamine);
        //ofLogNotice(to_string(finder.size()));
        
        /*ofLogNotice("#" + to_string(i));
         if (finder.size() > 0) {
         //ofLogNotice("FACE");
         imageFile.copyTo("/Volumes/WD\ My\ Passport\ -\ Samarth/Data/Image\ Datasets/faces/", false);
         }*/
        
        if(finder.size() > 0) {
            for(int j = 0; j < finder.size(); j++) {
                clippingMask = finder.getObject(j);
                temp.clone(fileImage);
                temp.crop(clippingMask.getX(), clippingMask.getY(), clippingMask.getWidth(), clippingMask.getHeight());
                temp.save("/Volumes/WD\ My\ Passport\ -\ Samarth/Data/Image\ Datasets/faces/" + to_string(face_count) + ".jpg", OF_IMAGE_QUALITY_BEST);
                temp.clear();
                face_count++;
            }
        }
        
        fileImage.clear();
        img.clear();
        imageToExamine.clear();
    }
    
}

void ofApp::setup() {
    ofSetVerticalSync(true);
    ofSetFrameRate(120);
    finder.setup("haarcascade_frontalface_alt.xml");
    finder.setPreset(ObjectFinder::Fast);
    //cam.setup(640, 480);
    
    string imageDir = "/Volumes/WD\ My\ Passport\ -\ Samarth/Data/Image\ Datasets/images-playing-cards/";
    ofLog() << "Gathering images...";
    ofDirectory dir = ofDirectory(imageDir);
    //scan_dir_imgs(dir);
    
    int size = dir.listDir();
    for(int i = 0; i < size; i++){
        imageFile = dir.getFile(i);
        fileImage.load(imageFile);
        img.setFromPixels(fileImage.getPixels());
        imageToExamine = img;
        finder.update(imageToExamine);
        //ofLogNotice(to_string(finder.size()));
        
        ofLogNotice("#" + to_string(i));
        if (finder.size() > 0) {
            //ofLogNotice("FACE");
            imageFile.copyTo("/Volumes/WD\ My\ Passport\ -\ Samarth/Data/Image\ Datasets/faces3/", false);
        }
        
        fileImage.clear();
        img.clear();
        imageToExamine.clear();
    }
    
    fileImage.load("card.jpg");
    //fileImage.load("/Volumes/WD My Passport - Samarth/Data/Image Datasets/face-test/180726_31aa32e768a8cbc1_b.jpg");
    img.setFromPixels(fileImage.getPixels());
    imageToExamine = img;
    
    //finder.update(imageToExamine);
    
    /*clippingMask = finder.getObject(0);
     ofLogNotice("width" + to_string(clippingMask.getWidth()));
     ofLogNotice("height" + to_string(clippingMask.getHeight()));
     ofLogNotice("x" + to_string(clippingMask.getX()));
     ofLogNotice("y" + to_string(clippingMask.getY()));
     
     fileImage.crop(clippingMask.getX(), clippingMask.getY(), clippingMask.getWidth(), clippingMask.getHeight());
     fileImage.save("face_crops/face_crop.jpg", OF_IMAGE_QUALITY_BEST);*/
}

void ofApp::update() {
    /*cam.update();
     if(cam.isFrameNew()) {
     finder.update(cam);
     }*/
    
    finder.update(imageToExamine);
}

void ofApp::draw() {
    //cam.draw(0, 0);
    
    imageToExamine.draw(0, 0);
    finder.draw();
    ofDrawBitmapStringHighlight(ofToString(finder.size()), 10, 20);
}
