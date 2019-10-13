/*
* Interactive art class
* Final task
* FEEL THE WATER - Main side
*
* 2019.7.21 Sun.
* Written by Masashi Seki
*/

#include "ofApp.h"

//Ocian
vector<Ripple *> ripples;
vector<Sunlight *> sunlights;
vector<Bubble *> bubbles;

//--------------------------------------------------------------
void ofApp::setup() {
	cout << "setup..." << endl;

	ofSetFrameRate(60);
	ofSetBackgroundColor(0, 0, 0);
	ofSetCircleResolution(64);
	ofHideCursor();
	//CGDisplayHideCursor(NULL);

	//Ocian
	background.load("background.jpg");
	fish1.load("fish1.png");
	fish1.load("fish2.png");
	fish1.load("fish3.png");
	fishes1.load("fishes1.png");
	fishes1.load("fishes2.png");
	bgm.load("Fountain.mp3");
	bgm.setLoop(true);
	bgm.play();

	w = ofGetWidth();
	h = ofGetHeight();

	for (int i = 0; i < 100; i++) {
		sunlights.push_back(new Sunlight(ofPoint(ofRandom(0, w*1.4), 0)));
	}

	//OSC
	receiver.setup(PORT);

	//Serial
	serial.setup("COM4", 9600); //Windows
	//serial.setup("/dev/tty.usbmodem1411",9600); //Mac
	sendByte = 0xFF;
	serial.writeByte(sendByte);

	e_rate = 0.5; //entire
	g_Line = 50; //ground
	black = true;
	counter = 0;
	fishAlive1 = false;
	fishAlive2 = false;
	fishAlive3 = false;
	fishesAlive1 = false;
	fishesAlive2 = false;
	angle = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

	//OSC
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		if (m.getAddress() == "/urg/handPos") {
			new_pos.x = m.getArgAsInt32(0);
			new_pos.y = m.getArgAsInt32(1);
		}

		//create ripple
		if (new_pos.x != 0 && new_pos.y != 0) {
			ripples.push_back(new Ripple(ofPoint(new_pos.x*e_rate + ofGetWidth() / 2, new_pos.y*e_rate + ofGetHeight() - g_Line), 1, 50, ofRandom(0, 100), 200, 255));
			ripples.push_back(new Ripple(ofPoint(new_pos.x*e_rate + ofGetWidth() / 2, new_pos.y*e_rate + ofGetHeight() - g_Line), 10, 3, 255, 255, 255));
			ripples.push_back(new Ripple(ofPoint(new_pos.x*e_rate + ofGetWidth() / 2, new_pos.y*e_rate + ofGetHeight() - g_Line), 15, 30, ofRandom(0, 100), 100, 255));
			ripples.push_back(new Ripple(ofPoint(new_pos.x*e_rate + ofGetWidth() / 2, new_pos.y*e_rate + ofGetHeight() - g_Line), 25, 3, 255, 255, 255));
			ripples.push_back(new Ripple(ofPoint(new_pos.x*e_rate + ofGetWidth() / 2, new_pos.y*e_rate + ofGetHeight() - g_Line), 30, 10, ofRandom(0, 100), 200, 255));
			//Ripple(ofPoint _pos, int _radius, int _lineWidth, int _r, int _g, int _b)
		}

		//hand position
		dist = 0;
		dist = ofDist(new_pos.x, new_pos.y, old_pos.x, old_pos.y);

		if (dist > 30) dist = 30;
		dist = ofMap(dist, 0, 30, 0, 100);
		old_pos = new_pos;

		cout << ".";
	}

	//ripple
	for (int i = 0; i < ripples.size(); i++) {
		ripples[i]->update();

		if (ripples[i]->dead == true) {
			//delete ripples[i];
			ripples.erase(ripples.begin() + i);
		}
	}

	//sunlight
	for (int i = 0; i < sunlights.size(); i++) {
		sunlights[i]->update();
	}

	//bubble
	for (int i = 0; i < bubbles.size(); i++) {
		bubbles[i]->update();

		if (bubbles[i]->dead == true) {
			bubbles.erase(bubbles.begin() + i);
		}

	}

	switch (counter) {
	case 1000:
		bubble_num = ofRandom(7, 20);
		for (int i = 0; i < bubble_num; i++) {
			bubbles.push_back(new Bubble(ofPoint(ofRandom(100, (w / 3)), ofRandom(h + 50, h + 500))));
		}
		break;

	case 2000:
		bubble_num = ofRandom(7, 20);
		for (int i = 0; i < bubble_num; i++) {
			bubbles.push_back(new Bubble(ofPoint(ofRandom((w / 3), (w / 3)*2), ofRandom(h + 50, h + 500))));
		}
		break;

	case 3000:
		bubble_num = ofRandom(7, 20);
		for (int i = 0; i < bubble_num; i++) {
			bubbles.push_back(new Bubble(ofPoint(ofRandom((w / 3) * 2, w - 100), ofRandom(h + 50, h + 500))));
		}
		break;

	case 0:
		fishPos1.x = w;
		fishPos1.y = ofRandom(0, (h / 2-100));
		fishAlive1 = true;
		break;

	case 800:
		fishPos2.x = w;
		fishPos2.y = ofRandom(0, (h / 2 - 100));
		fishAlive2 = true;
		break;

	case 1100:
		fishesPos1.x = w;
		fishesPos1.y = ofRandom(0, (h / 2 - 100));
		fishesAlive1 = true;
		break;

	case 1800:
		fishPos3.x = w;
		fishPos3.y = ofRandom(0, (h / 2 - 100));
		fishAlive3 = true;
		break;

	case 2500:
		fishesPos2.x = w;
		fishesPos2.y = ofRandom(0, (h / 2 - 100));
		fishesAlive2 = true;
		break;

	}

	//fish
	if (fishAlive1 == true) {
		fishPos1.x -= 1;
		if (fishPos1.x < -400)
			fishAlive1 = false;
	}
	if (fishAlive2 == true) {
		fishPos2.x -= 1;
		if (fishPos2.x < -400)
			fishAlive2 = false;
	}
	if (fishAlive3 == true) {
		fishPos3.x -= 1;
		if (fishPos3.x < -400)
			fishAlive3 = false;
	}
	if (fishesAlive1 == true) {
		fishesPos1.x -= 1;
		if (fishesPos1.x < -400)
			fishesAlive1 = false;
	}
	if (fishesAlive2 == true) {
		fishesPos2.x -= 1;
		if (fishesPos2.x < -400)
			fishesAlive2 = false;
	}

	angle += 0.1;
	if (angle > 360) angle = 0;

	//send to Arduino
	if (counter % 20 == 0) {
		sendByte = unsigned char(dist);
		serial.writeByte(sendByte);
	}

	//update counter
	counter++;
	if (counter > 3000)
		counter = 0;

	//cout << counter << endl;
	//cout << angle << endl;
}

//--------------------------------------------------------------
void ofApp::draw() {

	//Ocian
	background.draw(0, 0, w, h);

	//fish
	if (fishAlive1) fish1.draw(fishPos1.x, fishPos1.y + 100 * sin(angle * 0.017), 140, 140);
	if (fishAlive2) fish1.draw(fishPos2.x, fishPos2.y + 100 * sin((angle + 72) * 0.017), 160, 160);
	if (fishAlive3) fish1.draw(fishPos3.x, fishPos3.y + 100 * sin((angle + 144) * 0.017), 120, 120);
	if (fishesAlive1) fishes1.draw(fishesPos1.x, fishesPos1.y + 100 * sin((angle + 216) * 0.017), 200, 200);
	if (fishesAlive2) fishes1.draw(fishesPos2.x, fishesPos2.y + 100 * sin((angle + 288) * 0.017), 300, 300);

	//ripple
	ofPushStyle();
	ofEnableSmoothing();
	for (int i = 0; i < ripples.size(); i++) {
		ripples[i]->draw();
	}
	ofPopStyle();

	//sunlight
	ofPushStyle();
	ofEnableSmoothing();
	for (int i = 0; i < sunlights.size(); i++) {
		sunlights[i]->draw();
	}
	ofPopStyle();

	//bubble
	ofPushStyle();
	ofEnableSmoothing();
	for (int i = 0; i < bubbles.size(); i++) {
		bubbles[i]->draw();
	}
	ofPopStyle();

	/*
	ofPushStyle();
	ofSetColor(255, 0, 0);
	ofSetLineWidth(1);
	for (int i = 0; i < data_n; i++) {
		ofLine(ofGetWidth() / 2, ofGetHeight() - g_Line, point[i][0] * e_rate + ofGetWidth() / 2, point[i][1] * e_rate + ofGetHeight() - g_Line);
	}
	ofPopStyle();
	*/

	ofPushStyle();
	ofSetColor(255, 255, 0);
	ofFill();
	ofCircle(ofGetWidth() / 2, ofGetHeight() - g_Line, 5);
	ofPopStyle();

	ofPushStyle();
	ofSetColor(0, 255, 255);
	ofFill();
	ofCircle(new_pos.x*e_rate + ofGetWidth() / 2, new_pos.y*e_rate + ofGetHeight() - g_Line, 5);
	ofPopStyle();

	if (black == false) {

		ofPushStyle();
		ofSetColor(0, 255, 0);
		ofSetLineWidth(1);
		ofLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());
		ofLine(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() / 2);
		for (int i = 0; i < 10; i++) {
			ofLine(ofGetWidth() / 2 + i * 100, 0, ofGetWidth() / 2 + i * 100, ofGetHeight());
			ofLine(ofGetWidth() / 2 - i * 100, 0, ofGetWidth() / 2 - i * 100, ofGetHeight());
			ofLine(0, ofGetHeight() / 2 + i * 100, ofGetWidth(), ofGetHeight() / 2 + i * 100);
			ofLine(0, ofGetHeight() / 2 - i * 100, ofGetWidth(), ofGetHeight() / 2 - i * 100);
		}
		ofPopStyle();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//grid ON/OFF
	if (key == 'q') {
		black = !black;
	}
}
