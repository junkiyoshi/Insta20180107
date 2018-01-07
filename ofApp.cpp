#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofNoFill();
	ofSetLineWidth(6);
	ofSetCircleResolution(120);

	sound_stream.setup(this, 0, 1, 44100, 256, 4);
}

//--------------------------------------------------------------
void ofApp::update() {
	for (int i = 0; i < this->lengths.size(); i++) {
		this->lengths[i] += 2;
	}

	if (this->vol > 0.5) {
		ofColor color;
		color.setHsb(ofGetFrameNum() % 255, 255, 255);
		this->lengths.push_back(0);
		this->colors.push_back(color);
		this->vol = 0;
	}

	for (int i = this->lengths.size() - 1; i >= 0; i--) {
		if (this->lengths[i] > ofGetWidth()) {
			this->lengths.erase(this->lengths.begin() + i);
			this->colors.erase(this->colors.begin() + i);

		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (int i = 0; i < this->lengths.size(); i++) {
		ofSetColor(this->colors[i], 255 - this->lengths[i] / 2);
		ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, this->lengths[i]);
	}
}

//--------------------------------------------------------------
void ofApp::audioIn(float* input, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		this->vol += input[i] * input[i];
	}
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}