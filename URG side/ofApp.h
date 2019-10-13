/*
* Interactive art class
* Final task
* FEEL THE WATER - URG side
*
* 2019.7.21 Sun.
* Written by Masashi Seki
*/

#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "169.254.252.147" // ip address
#define PORT 8000 // port no.

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	//URG
	int counter;
	bool urgEnable;
	float e_rate; //entire
	int g_Line; //ground line

	//OSC
	ofxOscSender sender;
};
