/*
* Interactive art class
* Final task
* FEEL THE WATER - URG side
*
* 2019.7.21 Sun.
* Written by Masashi Seki
*/

#include "ofApp.h"

#include "Urg_driver.h"
#include "Connection_information.h"
#include "math_utilities.h"
#include <iostream>
#include <Lidar.h>

using namespace qrk;
using namespace std;

//URG
Urg_driver urg;
ofPoint handPos;
ofPoint handPosTmp;
size_t data_n;

namespace {

	void print_data(const Urg_driver& urg, const vector<long>& data, long time_stamp) {
#if 0
		int front_index = urg.step2index(0);
		cout << data[front_index] << " [mm], ("
			<< time_stamp << " [msec])" << endl;

#else
		long min_distance = urg.min_distance();
		long max_distance = urg.max_distance();
		data_n = data.size();
		long l;
		long counter = 0;
		double radian;
		handPos.x = 0;
		handPos.y = 0;
		handPosTmp.x = 0;
		handPosTmp.y = 0;

		for (size_t i = 0; i < data_n; ++i) {
			l = data[i];

			if ((l <= 300) || (l >= 1800)) { //from 300mm to 1800mm
				continue;
			}

			radian = urg.index2rad(i);

			handPosTmp.x += -1 * static_cast<long>(l * cos(radian - M_PI / 2));
			handPosTmp.y += static_cast<long>(l * sin(radian - M_PI / 2));
			counter++;
		}

		if (counter != 0) {
			handPos.x = handPosTmp.x / counter;
			handPos.y = handPosTmp.y / counter;
		}

#endif
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	cout << "setup..." << endl;

	ofSetFrameRate(60);
	ofSetBackgroundColor(75, 75, 75);

	int argc = 1;
	const char *argv[] = { "openF" };
	Connection_information information(argc, argv);

	if (!urg.open(information.device_or_ip_name(),
		information.baudrate_or_port_number(),
		information.connection_type())) {
		cout << "Urg_driver::open(): " << information.device_or_ip_name() << ": " << urg.what() << endl;
	}

#if 1
	urg.set_scanning_parameter(urg.deg2step(-90), urg.deg2step(+90), 0);
#endif

	e_rate = 0.6; //entire
	g_Line = 50; //ground
	counter = 0;
	urgEnable = true;

	//OSC
	sender.setup(HOST, PORT);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (counter % 3 == 0) {
		if (urgEnable == true) {
			vector<long> data;
			long time_stamp = 0;

			urg.start_measurement(Urg_driver::Distance, Urg_driver::Infinity_times, 0);
			if (!urg.get_distance(data, &time_stamp)) {
				cout << "Urg_driver::get_distance(): " << urg.what() << endl;
			}
			print_data(urg, data, time_stamp);
			urg.stop_measurement();

			if (handPos.x != 0 && handPos.y == 0) {
				handPos.x = 0;
				handPos.y = 0;
			}

				ofxOscMessage m;
				m.setAddress("/urg/handPos");
				m.addIntArg(handPos.x);
				m.addIntArg(handPos.y);
				sender.sendMessage(m);

			cout << ".";
		}
	}

	//update counter
	counter++;
	if (counter > 100)
		counter = 0;

#if defined(URG_MSC)
	getchar();
#endif
}

//--------------------------------------------------------------
void ofApp::draw() {

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
	ofCircle(ofGetWidth() / 2, ofGetHeight() - g_Line, 20);
	ofPopStyle();

	if (urgEnable == true) {
		ofPushStyle();
		ofSetColor(0, 255, 255);
		ofFill();
		ofCircle(handPos.x*e_rate + ofGetWidth() / 2, handPos.y*e_rate + ofGetHeight() - g_Line, 20);
		ofPopStyle();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		urgEnable = !urgEnable;
		if (urgEnable == false) urg.stop_measurement();
		cout << endl;
		cout << "urgEnable: " << urgEnable << endl;
	}
}

//--------------------------------------------------------------
