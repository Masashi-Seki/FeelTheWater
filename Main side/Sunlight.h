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

class Sunlight {
public:

	Sunlight(ofPoint _pos);
	~Sunlight();

	void update();
	void draw();

	int r, g, b;
	float a;
	ofPoint pos;
	ofPoint pos2;
	int lineWidth;
	bool toBright;
};
