#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofConstants.h"
#include "ofxVectorGraphics.h"
//#include "ofBufferObject.h"
#include "ofxPolylinesToSVG.h"
//#include "ofxEditableSVG.h"

#include <string>
//#include <iostream>
#include <fstream>




// 1056 816

#define gridW 1056
//2112
#define gridH 816
//1632
#define SVGW 297
#define SVGH 210

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
    
    
    double f;
    double k;
    double r;
    double dt;
    double du;
    double dv;
    
    int strkWidth;
    unsigned char* intermediateBuf;
    float* u[gridH]; // "grid"
    float* v[gridH];
    float* uu[gridH]; // "next"
    float* vv[gridH];
    
    float laplaceU(int x, int y);
    float laplaceV(int x, int y);
    
    ofImage refImg;
    unsigned char*  refPixBuf;
    
    //    contour finding stuff
    ofxCvGrayscaleImage     myImage;
    ofxCvGrayscaleImage     grayBg;
    ofxCvGrayscaleImage     grayDiff;
    ofxCvContourFinder     contourFinder;
    ofImage                 exportBlobImg;

    int                 thresholdVal;
    bool                bLearnBakground;
    bool                foundBlobs;
    
//    svg/eps stuff
    ofxVectorGraphics output;
    float svgScale;
    int frameCount;
    bool capture;
    // ofxPolylinesToSVG svg1; //diff layers
    // ofxPolylinesToSVG svg2;
    ofColor svgC1;
    ofColor svgC2;
    
    int svgW;
    int svgH;
    ofPolyline aPoly;
    ofxPolylinesToSVG *mySvgExporter1;
    ofxPolylinesToSVG *mySvgExporter2;
		
};
