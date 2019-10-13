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

class Ripple {
public:

	Ripple(ofPoint _pos, int radius, int _lineWidth, int _r, int _g, int _b);
	~Ripple();

	void update();
	void draw();

	int r, g, b;
	float a;
	ofPoint pos;
	float radius;
	int lineWidth;
	float expandRate;
	int timer;
	bool dead;

};
