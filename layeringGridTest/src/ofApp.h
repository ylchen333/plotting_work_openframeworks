#pragma once

#include "ofMain.h"
#include "ofxPolylinesToSVG.h"

#define gridW 1024
//1056
#define gridH 768
//816

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
    
    
    
        void drawGrad(float den, float xdisplace, float box);
    //        void drawGrad(void* funName, float den, float xdisplace, float box);
        void tenprintHatch(float x1, float y1, float x2, float y2, float spacing);
        float    box;
        vector<float> incre;
    
        int xPadding;
        int yPadding;
        int margin;
    
        ofPolyline aPoly1;
        ofColor svgC1;
        ofxPolylinesToSVG *mySvgExporter1;
        ofPolyline aPoly2;
        ofColor svgC2;
        ofxPolylinesToSVG *mySvgExporter2;
    
        float hache;
        int hhache;
		
};
