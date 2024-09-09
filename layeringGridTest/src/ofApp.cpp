#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    box = 110.0;
    incre.assign(5, 0.1);
    for (int i = 1 ; i < incre.size(); i ++ ){
        incre[i] = incre[i-1] + 0.2;
    }
    
    xPadding = 150;
    yPadding = 100;
    margin = 50;
    
    svgC1 = ofColor(255, 0, 255);
    mySvgExporter1 = new ofxPolylinesToSVG(1056,816);
    svgC2 = ofColor(0, 255, 255);
    mySvgExporter2 = new ofxPolylinesToSVG(1056,816);
}

//--------------------------------------------------------------
void ofApp::update(){

}
//--------------------------------------------------------------
//helpers that draw
void ofApp::tenprintHatch(float x1, float y1, float x2, float y2, float spacing) {
  // based on the iconoic 10 print pattern: https://10print.org

    for (float i = x1; (i) < x2; i += spacing){
        for(float j = y1; (j) < y2; j += spacing) {
            float xa = i ;
            float xb = i+spacing ;
            float ya = j;
            float yb = j +spacing ;
            if (ofRandom(1) < 0.5) {
                // xa = i - spacing/2 ;
                // xb = i+spacing;
                ya = j + spacing ;
                yb = j ;
            }
            //      ofLine(xa, ya, xb, yb);
            ofDrawLine(xa, ya, xb, yb);
        }
    }
}

//function<void(float, float, float, float, float)>
//(float, float, float, float, float)
void ofApp::drawGrad(float den, float xdisplace, float box){
  // print("\ndrawing hatching method " + str(funName));
    

    for (float i = 1; i < 6; i ++){
        float density = (roundf(den * incre[i-1] * i));
        // print("\nincre is " + incre[i-1]);
        // print("\ndensity is " + density);

        float y1 = 50+30*(i)+box*(i-1);
        float x1 = xdisplace;
        float y2 = 50 +30*(i)+box*(i);
        float x2 = xdisplace + box;
        tenprintHatch(x1, y1, x2, y2, density);

    // push();
    // stroke('magenta');
    // strokeWeight(3);
    // rect(x1, y1, box, box);
    // pop();

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(0, 0, 0);
    ofNoFill();
    ofSetColor(255, 0, 255);
    
//    ofDrawLine(0, 0, mouseX, mouseY);
    
//    tenprintHatch(20, 20, 50, 50, 15);
    
//    for(int x = margin/2; x < ofGetWidth()- margin; x +=25){
//        for(int y = margin/2; y < ofGetHeight()- margin; y +=25){
////            cout << ofGetWidth() - margin * 2 << '\n' ;
//            if ( x + ofGetWidth()- margin*2 < ofGetWidth()){
//                ofDrawLine(x, y, x+ofGetWidth()- margin*2, y);
//            }
//            if (y+ofGetHeight()- margin*2 < ofGetHeight()) {
//                ofDrawLine(x, y, x, y+ofGetHeight()- margin*2);
//            }
//        }
//    }
    
//    float squareSize = ;
    float W = ofGetWidth()-margin/2;
    float H = ofGetHeight()-margin/2;
    int h = margin/2;
//    
//    ofSetColor(255, 255, 0);
//    float increment = incre[(int)(ofRandom(incre.size()))];
//    for(int x = margin; x < ofGetWidth()-margin*2; x +=increment){
//        ofDrawLine(x, margin, x,margin+(ofGetHeight()-margin*2));
//    }
    incre.assign(1, 0.1);
//    ofSetRandomSeed(33);
    for (int d = 0; d < incre.size(); d ++ ) {
        float rS = (ofGetWidth()-margin*2)/incre.size();
        rS = (ofGetHeight()-margin*2)/incre.size();
        float rL = d*rS;
        float rR = rL + rS;
        float rT = 0;
        float rB = rT + rS;
        
        float hatchPercent = incre[d];
        int nLinesToDraw = round(hatchPercent * rS);
        float offset = (rS/nLinesToDraw)/2;
        
        
        // Vertical line version
        for (int j=0; j<nLinesToDraw; j++){
//            float lx = ofMap(j,0,nLinesToDraw, rL,rR) + offset + margin;
            float ly = ofMap(j,0,nLinesToDraw, rR,rL) + margin + offset;
            
            ofSetColor(0, 255, 255);
            if (ofNoise(1)*2 > 0.78){
                ofDrawLine(margin, ly, margin+(ofGetWidth()-margin*2), ly);
//                ofDrawLine(lx, margin+ rT, lx,margin+(ofGetHeight()-margin*2));
            }
            
            float offX = ofNoise(ly);
            float width = offX * (ofGetWidth()-margin*2);
            ofSetColor(255, 0, 255);
            if (ofNoise(1.0)*2 < 0.55){
                ofDrawLine(margin, ly + ofRandom(offX)*2, margin + width,ly + offX);
            }
            if (ofNoise(1.0)*2 > 0.9){
                ofDrawLine(margin+width, ly, ofGetWidth() - margin, ly - offX*2);
//                ofDrawLine(lx+offX, margin+ +height, lx-offX,margin+(ofGetHeight()-margin*2));
            }
        }
        
        
    }
    
    ofSetColor(0, 255, 255);
//    for (int d = 0; d < incre.size(); d ++ ) {
//        float rS = (ofGetHeight()-margin*2)/incre.size();
//        float rL = d*rS;
//        float rR = rL + rS;
//        float rT = 0;
//        float rB = rT + rS;
//        
//        float hatchPercent = incre[d];
//        int nLinesToDraw = round(hatchPercent * rS);
//        float offset = (rS/nLinesToDraw)/2;
//        
//        
//        // horizontal line version
//        for (int j=0; j<nLinesToDraw; j++){
//            float ly = H - margin/2 - ofMap(j,0,nLinesToDraw, rL,rR) - offset;
//            ofDrawLine(margin/2+ rT, ly, margin/2+(ofGetWidth()-margin), ly);
//        }
//    }

}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case 's':{
            float W = ofGetWidth()-margin/2;
            float H = ofGetHeight()-margin/2;
            int h = margin/2;
            
            
//            incre.assign(1, 0.1);
            for (int d = 0; d < incre.size(); d ++ ) {
                float rS = (ofGetWidth()-margin*2)/incre.size();
                rS = (ofGetHeight()-margin*2)/incre.size();
                float rL = d*rS;
                float rR = rL + rS;
                float rT = 0;
                float rB = rT + rS;
                
                float hatchPercent = incre[d];
                int nLinesToDraw = round(hatchPercent * rS);
                float offset = (rS/nLinesToDraw)/2;
                
                
                // Vertical line version
                for (int j=0; j<nLinesToDraw; j++){
                    //            float lx = ofMap(j,0,nLinesToDraw, rL,rR) + offset + margin;
                    float ly = ofMap(j,0,nLinesToDraw, rR,rL) + margin + offset;
                    
                    ofSetColor(0, 255, 255);
                    if (ofNoise(1)*2 > 0.78){
                        ofDrawLine(margin, ly, margin+(ofGetWidth()-margin*2), ly);
                        aPoly1.clear();
                        aPoly1.addVertex(margin, ly);
                        aPoly1.addVertex(margin+(ofGetWidth()-margin*2),ly);
                        mySvgExporter1->addPolyline(aPoly1, svgC1);
                        //                ofDrawLine(lx, margin+ rT, lx,margin+(ofGetHeight()-margin*2));
                    }
                    
                    
                    
                    float offX = ofNoise(ly);
                    float width = offX * (ofGetWidth()-margin*2);
                    ofSetColor(255, 0, 255);
                    if (ofNoise(1.0)*2 < 0.55){
                        ofDrawLine(margin, ly+ ofRandom(offX)*2, margin + width,ly + offX);
                        aPoly2.clear();
                        aPoly2.addVertex(margin, ly+ ofRandom(offX)*2);
                        aPoly2.addVertex(margin + width,ly + offX);
                        mySvgExporter2->addPolyline(aPoly2, svgC2);
                        
                    }
                    if (ofNoise(1.0)*2 > 0.9){
                        ofDrawLine(margin+width, ly, ofGetWidth() - margin, ly - offX*2);
                        aPoly2.clear();
                        aPoly2.addVertex(margin+width, ly);
                        aPoly2.addVertex(ofGetWidth() - margin,ly - offX*2);
                        mySvgExporter2->addPolyline(aPoly2, svgC2);
                        //                        aPoly2.clear();
                        //                        aPoly2.addVertex(lx+offX, margin+ +height);
                        //                        aPoly2.addVertex(lx,margin+(ofGetHeight()-margin*2));
                        //                        mySvgExporter2->addPolyline(aPoly2, svgC2);
                        //                ofDrawLine(lx+offX, margin+ +height, lx-offX,margin+(ofGetHeight()-margin*2));
                    }
                }
            }
//            for (int d = 0; d < incre.size(); d ++ ) {
//                float rS = (ofGetWidth()-margin*2)/incre.size();
//                float rL = d*rS;
//                float rR = rL + rS;
//                float rT = 0;
//                float rB = rT + rS;
//                
//                float hatchPercent = incre[d];
//                int nLinesToDraw = round(hatchPercent * rS);
//                float offset = (rS/nLinesToDraw)/2;
//                
//                
//                // Vertical line version
//                for (int j=0; j<nLinesToDraw; j++){
//                    float lx = ofMap(j,0,nLinesToDraw, rL,rR) + offset + margin;
//                    ofDrawLine(lx, margin+ rT, lx,margin+(ofGetHeight()-margin*2));
//                    aPoly1.clear();
//                    aPoly1.addVertex(lx, margin+ rT);
//                    aPoly1.addVertex(lx,margin+(ofGetHeight()-margin*2));
//                    mySvgExporter1->addPolyline(aPoly1, svgC1);
//                    
//                    float offX = ofNoise(lx);
//                    float height = offX * margin*2;
////                    ofSetColor(255, 0, 255);
////                    ofDrawLine(lx+offX, margin+ rT, lx,margin+height);
////                    ofDrawLine(lx+offX, margin+ +height, lx,margin+(ofGetHeight()-margin*2));
//                    aPoly2.clear();
//                    aPoly2.addVertex(lx+offX, margin+ rT);
//                    aPoly2.addVertex(lx,margin+height);
//                    mySvgExporter2->addPolyline(aPoly2, svgC2);
//                    aPoly2.clear();
//                    aPoly2.addVertex(lx+offX, margin+ +height);
//                    aPoly2.addVertex(lx,margin+(ofGetHeight()-margin*2));
//                    mySvgExporter2->addPolyline(aPoly2, svgC2);
////
//                }
//            }
//            
//            ofSetColor(255, 0, 255);
//            for (int d = 0; d < incre.size(); d ++ ) {
//                float rS = (ofGetWidth()-margin*2)/incre.size();
//                float rL = d*rS;
//                float rR = rL + rS;
//                float rT = 0;
//                float rB = rT + rS;
//                
//                float hatchPercent = incre[d];
//                int nLinesToDraw = round(hatchPercent * rS);
//                float offset = (rS/nLinesToDraw)/2;
//                
//                
//                // Vertical line version
//                for (int j=0; j<nLinesToDraw; j++){
//                    float lx = W - margin/2 - ofMap(j,0,nLinesToDraw, rL,rR) - offset;
////                    ofDrawLine(lx, margin/2+ rT, lx,margin/2+(ofGetHeight()-margin));
//                    aPoly1.clear();
//                    aPoly1.addVertex(lx, margin/2+ rT);
//                    aPoly1.addVertex(lx,margin/2+(ofGetHeight()-margin));
//                    mySvgExporter1->addPolyline(aPoly1, svgC1);
//                    
//                }
//            }
            
//            ofSetColor(0, 255, 255);
//            for (int d = 0; d < incre.size(); d ++ ) {
//                float rS = (ofGetHeight()-margin*2)/incre.size();
//                float rL = d*rS;
//                float rR = rL + rS;
//                float rT = 0;
//                float rB = rT + rS;
//                
//                float hatchPercent = incre[d];
//                int nLinesToDraw = round(hatchPercent * rS);
//                float offset = (rS/nLinesToDraw)/2;
//                
//                
//                // horizontal line version
//                for (int j=0; j<nLinesToDraw; j++){
//                    float ly = H - margin/2 - ofMap(j,0,nLinesToDraw, rL,rR) - offset;
////                    ofDrawLine(margin/2+ rT, ly, margin/2+(ofGetWidth()-margin), ly);
//                    aPoly2.clear();
//                    aPoly2.addVertex(margin/2+ rT, ly);
//                    aPoly2.addVertex(margin/2+(ofGetWidth()-margin), ly);
//                    mySvgExporter2->addPolyline(aPoly2, svgC2);
//                }
//            }
//            for(int x = 50; x < ofGetWidth()-55-xPadding; x+=xPadding){
//                int den = 0;
//                for(int y = 50; y < ofGetHeight()-55-yPadding; y+=yPadding){
//                    
//                    float density = incre[den]*20;
//                    
//                    for(int j = 1; j < yPadding; j += density){
////                        ofDrawLine(x, y+j, x+xPadding-5, y+j);
////                        ofDrawLine(x+j, y, x+j, y+yPadding-5);
//
//                    }
//                    den ++;
//                    
//                }
//            }
            
            string svgFileName1 = "lt_lines_c1_" + ofToString(roundf(ofGetFrameNum()))+ ".svg";
            string svgFileName2 = "lt_lines_c2_" + ofToString(roundf(ofGetFrameNum()))+ ".svg";
            
//            svgFileName = "HELP_" + ofToStrinsg(contourFinder.nBlobs) + ".svg";
            mySvgExporter1->saveToFile(svgFileName1);
            mySvgExporter2->saveToFile(svgFileName2);
            
            cout << "exported " << svgFileName1 << endl;
            cout << "exported " << svgFileName2 << endl;
            
        }
            
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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
