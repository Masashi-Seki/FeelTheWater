/*
* Interactive art class
* Final task
* FEEL THE WATER - Main side
*
* 2019.7.21 Sun.
* Written by Masashi Seki
*/

#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#include "ofMain.h"
#include "Ripple.h"
#include "Sunlight.h"
#include "Bubble.h"
#include "ofxOsc.h"

#define PORT 8000

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	//Ocian
	int w, h;
	int dist;
	int counter;
	ofImage background;
	ofPoint new_pos;
	ofPoint old_pos;
	int bubble_num;

	//Serial
	ofSerial serial;
	unsigned char sendByte;

	//OSC
	ofxOscReceiver receiver;

	//common
	float e_rate;
	float g_Line;
	bool black;

	//fish
	ofImage fish1;
	ofImage fish2;
	ofImage fish3;
	ofImage fishes1;
	ofImage fishes2;

	ofPoint fishPos1;
	ofPoint fishPos2;
	ofPoint fishPos3;
	ofPoint fishesPos1;
	ofPoint fishesPos2;

	bool fishAlive1;
	bool fishAlive2;
	bool fishAlive3;
	bool fishesAlive1;
	bool fishesAlive2;

	float angle;
	ofSoundPlayer bgm;

};
