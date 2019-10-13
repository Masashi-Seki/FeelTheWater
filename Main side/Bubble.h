/*
* Interactive art class
* Final task
* FEEL THE WATER - Main side
*
* 2019.7.21 Sun.
* Written by Masashi Seki
*/

#pragma once

#include "ofApp.h"

class Bubble {
public:

	Bubble(ofPoint _pos);
	~Bubble();

	void update();
	void draw();

	int r, g, b;
	float a;
	ofPoint pos;
	bool dead;
	int angle;
	int size;
	int amp_x;
};
