/*
* Interactive art class
* Final task
* FEEL THE WATER - Main side
*
* 2019.7.21 Sun.
* Written by Masashi Seki
*/

#include "Ripple.h"
#include "ofApp.h"

Ripple::Ripple(ofPoint _pos, int _radius, int _lineWidth, int _r, int _g, int _b) {

	pos = _pos;
	r = _r;
	g = _g;
	b = _b;
	a = 150;

	lineWidth = _lineWidth;
	radius = _radius;
	expandRate = 1;

	dead = false;
	timer = 500;
}

Ripple::~Ripple() {
	/*
	for (int i = 0; i < ripples.size(); i++) {
		ripples.erase(ripples.begin() + i);
	}
	*/
}

void Ripple::update() {
	radius += expandRate;

	timer -= 1;
	a -= 1;

	if (timer < 0) {
		dead = true;
	}

}

void Ripple::draw() {

	ofSetColor(r, g, b, a);
	ofNoFill();
	ofSetLineWidth(lineWidth);
	ofCircle(pos.x, pos.y, radius);

}
