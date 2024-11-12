#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#include "NoiseField.h"
#include "NoiseLoop.h"
#include "Scope.h"
#include "Mixer.h"
#include "Clocker.h"

#define SEND_PORT 8000
#define RECEIVE_PORT 7002

#define NUM_LOOPS 6

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		NoiseField field;
		NoiseLoop loops[NUM_LOOPS];
		Xfader xf;
		Mixer mix;
		Clocker clock;

		vector<float> noiseVals;

		bool bDrawGui;

		ofParameterGroup loop_params;

		ofxPanel gui;
		ofxOscSender sender;
		ofxOscReceiver receiver;

		
};
