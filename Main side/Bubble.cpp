/*
* Interactive art class
* Final task
* FEEL THE WATER - Main side
*
* 2019.7.21 Sun.
* Written by Masashi Seki
*/

#include "Bubble.h"
#include "ofApp.h"
#include <math.h>

Bubble::Bubble(ofPoint _pos){
	pos = _pos;
	r = g = b = 255;
	a = ofRandom(70, 120);
	dead = false;
	angle = ofRandom(0, 360);
	size = ofRandom(7, 17);
}

Bubble::~Bubble() {

}

void Bubble::update() {
	pos.y += -1;
	amp_x = 10 * sin(angle * M_PI / 180);
	a -= 0.05;

	if ((pos.y < -1 * size) || (a < 0)) dead = true;

	angle++;
	if (angle > 360) angle = 0;
}

void Bubble::draw() {
	ofSetColor(r, g, b, a);
	ofFill();
	ofCircle(pos.x + amp_x, pos.y, size);
}
