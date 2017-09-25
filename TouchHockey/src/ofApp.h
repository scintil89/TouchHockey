#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxTuioClient.h"
#include "Ball.h"
#include "Bar.h"
#include <vector>
#include <map>

class ofApp : public ofBaseApp 
{

public:
	void setup();
	void update();
	void draw();

	static ofApp* GetInstance()
	{
		return instance;
	}

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void touchDown(ofTouchEventArgs & touch);
	void touchUp(ofTouchEventArgs & touch);
	void touchMoved(ofTouchEventArgs & touch);


private:
	void inputDown(ofPoint p);
	void CollisionBallWithMap(Ball* b);
	void CheckHP();

	ofxTuioClient myTuio;


	void ResetGame();



private:
	std::vector<Ball*> balls;
	std::map<int, ofPoint> inputMap;

	//Bar* RedPlayer;
	//Bar* BluePlayer;
	
	int player1Hp;
	int player2Hp;

	ofSoundPlayer collisionlSound;
	ofSoundPlayer downHPSound;
	ofSoundPlayer wallCollisionSound;
	ofSoundPlayer bellSound;
	ofSoundPlayer buzzerSound;

	static ofApp* instance;

	bool isRun;
	bool endSound;

	ofTrueTypeFont font;
	ofTrueTypeFont font2;
};

#endif
