#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(60);
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(ofColor::fromHsb(hue, 255, 255));
    ofFill();
    ofCircle(ofGetWidth()/2, ofGetHeight()/2, radius/5 + ofRandom(-5, 5));
    ofNoFill();
    ofCircle(ofGetWidth()/2, ofGetHeight()/2, radius + ofRandom(-5, 5));
    ofLine(ofGetWidth()/2, ofGetHeight()/2, mouseX, mouseY);
    
    ofSetColor(0, 0, 0, 150);
    for (int i = 0; i < 30; i++) {
        ofLine(ofGetWidth()/30*i, 0, ofGetWidth()/30*i, 768);
    }
    for (int i = 0; i < 20; i++) {
        ofLine(0, ofGetHeight()/20*i, 1024, ofGetHeight()/20*i);
    }

    // 十字に線引いてる
    ofLine(mouseX, 0, mouseX, ofGetHeight());
    ofLine(0, mouseY, ofGetWidth(), mouseY);
    
    ofDrawBitmapString("radius: " + ofToString(radius), mouseX+20, mouseY+20);
    ofDrawBitmapString("deg: " + ofToString(deg), mouseX+20, mouseY+40);
    
    // meshの部分

    mesh.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    mesh.clear();
    
    // マウスと円の距離測定
    length = ofDist(ofGetWidth()/2, ofGetHeight()/2, x, y);
    radius = length;
    
    // radでなす角取得
    angle = asin((ofGetHeight()/2 - y)/radius);
    
    // radからdegに変換
    deg = angle * 180 / PI;
    
    // 座標が左側にあるときの処理
    if (x < ofGetWidth()/2) {
        deg = 180 - (angle * 180 / PI);
    }
    // 座標が右下にあるときの処理
    if (y > ofGetHeight()/2 && x > ofGetWidth()/2){
        deg = 360 + (angle * 180 / PI);
    }
    
    // 円の3時にあたる座標と、円の中心を追加
    mesh.addVertex(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
    mesh.addVertex(ofVec3f(ofGetWidth()/2 + radius, ofGetHeight()/2, 0));
    
    for (float i = 0; i < deg; i += 0.5) {
        // 1° = PI / 180 rad
        // 円周上の頂点情報を取得してる
        float point_x = radius * cos(i * PI / 180) + ofGetWidth()/2;
        float point_y = - radius * sin(i * PI / 180) + ofGetHeight()/2;
        
        // 円周上の頂点情報を1°毎に追加してる
        mesh.addVertex(ofVec3f(point_x, point_y, 0));
    }
    
    mesh.draw();
    
    // 0~360°をHSBの0~255にマッピング
    hue = ofMap(deg, 0, 360, 0, 255);

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
