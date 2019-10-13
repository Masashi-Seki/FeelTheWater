/*
* Interactive art class
* Final task
* FEEL THE WATER - Main side
*
* 2019.7.21 Sun.
* Written by Masashi Seki
*/

#include "Sunlight.h"
#include "ofApp.h"

Sunlight::Sunlight(ofPoint _pos) {
	r = 255;
	g = 255;
	b = 255;
	a = ofRandom(0, -100);
	pos = _pos;
	pos2.x = pos.x - ofRandom(100, 200);
	pos2.y = 3 * abs(pos2.x - pos.x);
	lineWidth = ofRandom(1, 20);
	toBright = false;
}

Sunlight::~Sunlight() {
	/*
	for (int i = 0; i < sunlights.size(); i++) {
		sunlights.erase(sunlights.begin() + i);
	}
	*/
}

void Sunlight::update() {
	if (toBright == true) {
		a += 0.5;
		if (a > 20) toBright = false;
	}
	else {
		a -= 0.5;
		if (a < 0) toBright = true;
	}

}

void Sunlight::draw() {
	ofSetColor(r, g, b, a);
	ofFill();
	ofSetLineWidth(lineWidth);
	ofLine(pos.x, pos.y, pos2.x, pos2.y);
}
