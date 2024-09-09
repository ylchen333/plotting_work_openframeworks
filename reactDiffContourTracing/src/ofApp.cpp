#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(10000);
    ofSetVerticalSync(false);
    thresholdVal = 128;
    svgScale = SVGW / gridW;
    frameCount = 0;
    capture = false;
    refImg.load("moldref.png");
    refImg.crop(0, 0, gridW, gridH);
    refPixBuf = refImg.getPixels().getData();
    strkWidth = 10;
    
    f = 0.04; //0.033; // 0.0962; //0.047; //0.04;
    k = 0.06; //0.063; // 0.05560; //0.062; //0.06;
    r = 0.01;
    dt = 0.01;
    du = 1.0;
    dv = 0.5;
    
    myImage.allocate(gridW,gridH);
    exportBlobImg.allocate(gridW, gridH, OF_IMAGE_GRAYSCALE);
    
    
//    initialize svg stuff
//    ofxPolylinesToSVG svg1.setSize(100, 100);
//    ofxPolylinesToSVG svg2.setSize(100, 100);
    svgW = 1056;
    svgH = 816;
    mySvgExporter1 = new ofxPolylinesToSVG(svgW,svgH);
    mySvgExporter2 = new ofxPolylinesToSVG(svgW,svgH);
    svgC1 = ofColor(0, 250, 250); //cyan?
    svgC2 = ofColor(250, 0, 250); //magenta?
    
//    fill arrays
    for (int i=0; i<gridH; i++){
        u[i] = new float[gridW];
        v[i] = new float[gridW];
        uu[i] = new float[gridW];
        vv[i] = new float[gridW];
    }
    
    intermediateBuf = new unsigned char[gridW * gridH];
//    fill our array with slightly random points
    for (int i = 0; i < gridH; i++) {
        for (int j = 0; j < gridW; j++) {
            uu[i][j] = u[i][j] = ofRandom(0.8,1.0);
            vv[i][j] = v[i][j] = ofRandom(0.0,0.2);
        }
    }
    
//    starting spawn point
    
//    for (int i = gridH/4; i < gridH/4*3; i+=30) {
//        for (int j = gridW/4; j < gridW/4*3; j+=30) {
//            float factor = ofDist(gridW/2, gridH/2, (float)j, (float)i);
//            factor = ofMap(factor, 0, ofDist(0.0, 0.0, gridW/2, gridH/2), 2, 0);
//            if (factor > 1.8){
//                int ip1 = i+1;
//                int im1 = i-1;
//                int jp1 = j+1;
//                int jm1 = j-1;
//                v[i][j] = ofNoise(1.0);
//                v[i][jm1] = ofNoise(1.0);
//                v[i][jp1] = ofNoise(1.0);
//                v[ip1][j] = ofNoise(1.0);
//                v[im1][j] = ofNoise(1.0);
//                v[im1][jm1] = ofNoise(1.0);
//                v[im1][jp1] = ofNoise(1.0);
//                v[ip1][jp1] = ofNoise(1.0);
//                v[ip1][jm1] = ofNoise(1.0);
//                
//                if (factor > 1.8){
//                    v[i][jm1--] = ofNoise(1.0);
//                    v[i][jp1++] = ofNoise(1.0);
//                    v[ip1++][j] = ofNoise(1.0);
//                    v[im1--][j] = ofNoise(1.0);
//                }
//                v[im1--][jm1--] = ofNoise(1.0);
//                v[im1--][jp1++] = ofNoise(1.0);
//                v[ip1++][jp1++] = ofNoise(1.0);
//                v[ip1++][jm1--] = ofNoise(1.0);
//                if (factor < 1.2) {
//                    v[i][jm1--] = ofNoise(1.0);
//                    v[i][jp1++] = ofNoise(1.0);
//                    v[ip1++][j] = ofNoise(1.0);
//                    v[im1--][j] = ofNoise(1.0);
//                }
//                v[im1--][jm1--] = ofNoise(1.0);
//                v[im1--][jp1++] = ofNoise(1.0);
//                v[ip1++][jp1++] = ofNoise(1.0);
//                v[ip1++][jm1--] = ofNoise(1.0);
//            }
//                
//        }
//    }
////
//    
//    

}

//--------------------------------------------------------------
void ofApp::update(){

//    printf("Hello Lorie %f\n", ofGetFrameRate());
    frameCount++;
    int niteration = 2;
//    simmulate niterarations
    for(int n = 0; n < niteration; n++){
        
        int collatz = roundf(ofRandom(gridH));
        for (int y = 1; y < gridH - 1; y++) {
            for (int x = 1; x < gridW - 1; x++) {
                int idx = y*gridW + x;
                double feed = f;
                double kill = k;
            
                double sourcePxF = (double) refPixBuf[idx+1];
                double sourcePxK = (double) refPixBuf[idx];
                
//                change feed and kill rates
//                float angle = ofMap(sourcePxF, 0, 255, 0.0, 360.0);
//                feed = ofMap(sourcePxF, 0, 255, -0.03, 0.06);  //+ k/sin(sourcePxF/66)
//                feed -= sin(angle)*0.05;
//                kill += ofMap(sourcePxK, 0, 200, -0.0444, 0.03); // + f/cos(sourcePxK/66)
//                feed = f*sin(sourcePxF%22);
//                feed = f*atan2((double)y, (double)x) + f/1.5;
//                kill = feed + sourcePxK/500;
//                kill = k*atan2((double)x, (double)y)+k/3;
//                feed = ofMap(atan2(x, y), 0, 360, f, f+0.01);
//                kill = ofMap(y, 1, gridH, k-0.02, k+0.02);
//                double diffFK = f-k;
//                feed = ofMap(ofDist(0, 0, (float)x, (float)y),0,  ofDist(0.0, 0.0, gridW*2, gridH*2), f-0.09, f+0.01);
//                feed += ofMap(ofNoise(sourcePxF), 0.0, 1.0, f, f+diffFK);
//                feed = ofMap(ofNoise(sourcePxF), 0.0, 1.0, f-0.1, f+0.1);
//                feed = ofRandom(-0.5, 0.5) * sourcePxF;
//                float angleKill = ofMap(sourcePxK, 0, 255, 0.0, 360.0);
//                float diff = sin(angle)*2;
//                kill += ofMap(ofDist(gridW, gridH, (float)x-gridW/1.4, (float)y+gridH/2) ,0,  ofDist(0.0, 0.0, gridW*2, gridH*2), k-0.01, k);
//                if (ofDist(gridW, gridH, (float)x, (float)y) > 300 &&
//                    ofDist(gridW, gridH, (float)x, (float)y) < 500 ){
//                    kill += ofRandom(2);
//                }
//                kill += tan(angleKill)*0.01;
//                feed += floor(sourcePxF/50)*0.01;
//                kill += floor(sourcePxK/50)*0.01;
//                feed += ofMap(sin(sourcePxF), 0, 1, -0.008, 0.007);
//                kill = ofMap(atan(sourcePxK), 0, 1, 0, k);
                
//                feed += ofRandom(-0.09, -0.01);
//                kill += ofRandom(-0.04, -0.001);
//                cout << "feed: " << feed << endl;
//                cout << "kill: " << kill << endl;
                
                float a = u[y][x]; // grid
                float b = v[y][x]; // grid
                float abb = (a * b * b);
                uu[y][x] = a + (du * laplaceU(x, y)) - abb + (feed * (1 - a)) ;
                vv[y][x] = b + (dv * laplaceV(x, y)) + abb - ((kill + feed) * b);
                uu[y][x] = MAX(0,MIN(1,uu[y][x]));
                vv[y][x] = MAX(0,MIN(1,vv[y][x]));
            }
        }
        
        
        for (int i = 0; i < gridH; i++) {
            float* tempUArr = u[i];
            float* tempUUArr = uu[i];
            float* tempVArr = v[i];
            float* tempVVarr = vv[i];
            for (int j = 0; j < gridW; j++) {
                float tempU = tempUArr[j];
                u[i][j] = tempUUArr[j];
                uu[i][j] = tempU;
                
                float tempV = tempVArr[j];
                v[i][j] = tempVVarr[j];
                vv[i][j] = tempV;
            }
        }
        
    }
    
    
    
    
    // Gets the value into the buffer
    int dstIndex = 0;
    for (int i = 0; i < gridH; i++) {
        for (int j = 0; j < gridW; j++) {
            float a = uu[i][j];
            float b = vv[i][j];
            unsigned char c = (unsigned char) (255 - MAX(0,MIN(1,(a - b))) * 255);
            intermediateBuf[dstIndex++] = c;
        }
    }
    
    myImage.setFromPixels(intermediateBuf, gridW, gridH);
    myImage.threshold(thresholdVal);
    
    
//    find contours
    int minBlob = 2; // roundf(ofRandom(5, 20));
    int maxBlob = (int)(gridW * gridH *0.7);
    contourFinder.findContours(myImage, minBlob, maxBlob, 500, true);
    foundBlobs = true;
    

    
}



inline float ofApp::laplaceU(const int x, const int y) {
    const int yp1 = y+1;
    const int ym1 = y-1;
    const int xp1 = x+1;
    const int xm1 = x-1;
    float sumA = u[y][x] * -1; // -3
    sumA += (u[y][xm1] +
             u[y][xp1] +
             u[yp1][x] +
             u[ym1][x])*0.2; //0.5
    sumA += (u[ym1][xm1] +
             u[ym1][xp1] +
             u[yp1][xp1] +
             u[yp1][xm1])*0.05; // 0.25
    return sumA;
}

inline float ofApp::laplaceV(const int x, const int y) {
    const int yp1 = y+1;
    const int ym1 = y-1;
    const int xp1 = x+1;
    const int xm1 = x-1;
    float sumB = v[y][x] * -1;
    sumB += (v[y][xm1] +
             v[y][xp1] +
             v[yp1][x] +
             v[ym1][x])*0.2;
    sumB += (v[ym1][xm1] +
             v[ym1][xp1] +
             v[yp1][xp1] +
             v[yp1][xm1])*0.05;
    return sumB;
}




//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(0, 0, 0);
    ofNoFill();
    ofSetColor(255,255,255);
    
    myImage.draw(0,0);
    
   
    if(foundBlobs){
        ofPolyline ithPoly;
        for (int i = 0; i < contourFinder.nBlobs; i++){
            // contourFinder.blobs[i].draw(0,0);
            ithPoly.clear();
            ofxCvBlob ithBlob = contourFinder.blobs[i];
            int nPointsInBlob = ithBlob.nPts;
//            choose a color based on if its a hole or not
            ofColor ithColor;
            if (ithBlob.area > 250){
                ithColor = svgC1;
            } else {
                ithColor = svgC2;
            }
//            cout << i << "th blob has color " << ithColor << endl;
            
            for (int j=0; j<nPointsInBlob+1; j++){
                //                        add each point in ithBlob into a polyline
                glm::vec3 jthPoint = ithBlob.pts[(j+nPointsInBlob)%nPointsInBlob];
                ithPoly.addVertex(jthPoint.x, jthPoint.y, jthPoint.z);
            }
            
            //                    smooth our blob
            ithPoly.getSmoothed(10);
            ofSetColor(ithColor);
            ofNoFill();
            ithPoly.draw();
//            mySvgExporter1->addPolyline(ithPoly, ithColor);
        }

//
        
//        capture =false;
    }

    //
    // End capture!
    //-------------------------
    //-------------------------
    
    
    ofSetColor(111,255,255);
    string sfr = "Frame Rate: ";
    sfr += ofToString(ofGetFrameRate());
    ofDrawBitmapString(sfr, 10, gridH - 50);
    
    string snb = "nBlobs = " + ofToString(contourFinder.nBlobs);
    ofDrawBitmapString(snb, 10, gridH - 70);
    
    string feedStr = "(change with o/p) feed: " + ofToString(f);
    ofDrawBitmapString(feedStr, 10, gridH - 110);
    
    string killStr = "(change with o/p) kill: " + ofToString(k);
    ofDrawBitmapString(killStr, 10, gridH - 130);
    
    string svgStr = "press s to save svg";
    ofDrawBitmapString(svgStr, 10, gridH - 90);
    
    string thresStr = "(change with -/+) threshold: " + ofToString(thresholdVal);
    ofDrawBitmapString(thresStr, 10, gridH - 30);
    
    string strkWStr = "(change with n/m) strkWidth: " + ofToString(strkWidth);
    ofDrawBitmapString(strkWStr, 10, gridH - 10);
    
    
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------

//--------------------------------------------------------------


void ofApp::keyPressed(int key){
    switch (key) {
        case 'p':{
            f+= 0.001;
            break;
        }
        case 'o':{
            f-=0.001;
            break;
        } 
        case 'w':{
            k+= 0.001;
            break;
        }
        case 'q':{
            k-=0.001;
            break;
        }
        case '=':{
                thresholdVal++;
                break;
            }
        case '-':{
                thresholdVal--;
                break;
            }
        case 'n':{
                strkWidth--;
                break;
            }
        case 'm':{
                strkWidth++;
                break;
            }
        case 'r':{
//            restart reaction
            setup();
            break;
            }
        case 'i':{
//            export thresholded image
//            exportBlobImg.grabScreen(0, 0, gridW, gridH);
            exportBlobImg.setFromPixels(intermediateBuf, gridW, gridH, OF_IMAGE_GRAYSCALE);
            string imgName = "rdcontour_" + ofToString(ofGetFrameNum()) +
            "_" + ofToString(contourFinder.nBlobs) + ".jpg";
            exportBlobImg.save(imgName);
            cout << "exported " << imgName << endl;
            break;
        }
//
        case 's':{
//            //        export svg
//            capture = true;
            ofPolyline ithPoly;
            for (int i = 0; i < contourFinder.nBlobs; i++){
                // contourFinder.blobs[i].draw(0,0);
                ithPoly.clear();
                ofxCvBlob ithBlob = contourFinder.blobs[i];
                int nPointsInBlob = ithBlob.nPts;
//                cout << " the " << i << "th blob has " << nPointsInBlob << " points in it" << endl;
//                cout << " this blob hole: " << ithBlob.hole << endl;
    //            choose a color based on if its a hole or not
                ofColor ithColor;
                if (ithBlob.hole){
                    ithColor = svgC1;
                } else {
                    ithColor = svgC2;
                }
                
                for (int j=0; j<nPointsInBlob+2; j++){
                    //                        add each point in ithBlob into a polyline
                    glm::vec3 jthPoint = ithBlob.pts[(j+nPointsInBlob)%nPointsInBlob];
    //                cout << "jthpoint.x " << jthPoint.x << "-- type of "<< typeid(jthPoint.x).name() << endl;
    //                cout << "jthpoint.y " << jthPoint.y << "-- type of "<< typeid(jthPoint.y).name() << endl;
                    ithPoly.addVertex(jthPoint.x, jthPoint.y);
                }
//                cout << ithPoly << endl;
                //                    smooth our blob
                ithPoly.getSmoothed(10);
                
                if (ithBlob.hole){
                    mySvgExporter1->addPolyline(ithPoly, ithColor);
                } else {
                    mySvgExporter2->addPolyline(ithPoly, ithColor);
                }
                
            }
                   
            string svgFileName1 = "rdcontour_c1_" + ofToString(ofGetFrameRate()) +
                                         "_" + ofToString(contourFinder.nBlobs) + ".svg";
            string svgFileName2 = "rdcontour_c2_" + ofToString(ofGetFrameRate()) +
                                         "_" + ofToString(contourFinder.nBlobs) + ".svg";

            mySvgExporter1->saveToFile(svgFileName1);
            mySvgExporter2->saveToFile(svgFileName2);
            
            cout << "exported " << svgFileName1 << endl;
            cout << "exported " << svgFileName2 << endl;
            break;
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
    
    for (int i = y -strkWidth; i < y +strkWidth; i++) {
        for (int j = x -strkWidth; j < x + strkWidth; j++) {
            float circ = ofDist((float)x, (float)y, (float)j, (float)i);
            if (i >= 0 && i < gridH &&j >= 0 && j < gridW && (circ <= strkWidth)) {
            
                v[i][j] = 1.0;
            }
                
        }
    }
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





//--------------------------------------------------------------
//dead
//            free((void *) mySvgExporter1);
//            mySvgExporter1 =  new ofxPolylinesToSVG(svgW,svgH);
//            free((void *) mySvgExporter2);
//            mySvgExporter2 =  new ofxPolylinesToSVG(svgW,svgH);
//            createSVG(contourFinder, svgScale);

////            for (int i = 0; i < contourFinder.nBlobs; i++){
////                ofxCvBlob ithBlob = contourFinder.blobs[i];
////                int nPointsInBlob = ithBlob.nPts;
////                //                    decide what svg color to export to
////                ofColor ithColor;
////                if (ithBlob.hole){
////                    ithColor = svgC1;
////                } else {
////                    ithColor = svgC2;
////                }
//////                ofPolyline ithPoly;
//////                for (int j=0; j<nPointsInBlob; j++){
//////                    //                        add each point in ithBlob into a polyline
//////                    glm::vec3 jthPoint = ithBlob.pts[j];
//////                    //                        ofVec3f jthPtConverted = ofVec3f(ithBlob.pts[j].x,ithBlob.pts[j].y,0);
//////                    ithPoly.addVertex(ithBlob.pts[j].x, ithBlob.pts[j].y);
//////                }
//////
//////                //                    smooth our blob
//////                ithPoly.getSmoothed(10);
//////
//////                svg1.addPolyline(ithPoly, ithColor);
////                //  svg.addCircle(poly, color);
////            }
//            //                save the resulting svg
////            string svgFileName = "svg1_fc-" + ofToString(frameCount) +
////                                 "_nblob-" + ofToString(contourFinder.nBlobs) + ".svg";
////            svg1.saveToFile(svgFileName);
//            break;
