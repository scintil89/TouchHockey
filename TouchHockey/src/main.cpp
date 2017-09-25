#include "ofMain.h"
#include "ofApp.h"
#include "Common.h"

//========================================================================

int main() {
	ofSetupOpenGL(Common::width, Common::height, OF_FULLSCREEN);			// <-------- setup the GL context

													// this kicks off the running of my app
													// can be OF_WINDOW or OF_FULLSCREEN
													// pass in width and height too:
	ofRunApp(new ofApp());
}
