#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(100, 100, 100);
	//ofSetVerticalSync(true);

	ofSetFrameRate(120);

	//Connect to Port
	myTuio.connect(3333);


	//Assign Global TUIO Callback Functions
	ofAddListener(ofEvents().touchDown, this, &ofApp::touchDown);
	ofAddListener(ofEvents().touchUp, this, &ofApp::touchUp);
	ofAddListener(ofEvents().touchMoved, this, &ofApp::touchMoved);

	//set up
	inputMap.clear();

	//New Ball
	Ball* newBall = new Ball(500, 100, Common::PLAYERINFO::Player1);
	newBall->setup();
	newBall->SetColor(ofColor::purple);
	//newBall->SetPlayerInfo(Common::PLAYERINFO::Player1);
	balls.push_back(newBall);

	//SetBar
	//RedPlayer = new Bar();
	//RedPlayer->Setup();
	//
	//BluePlayer = new Bar();
	//BluePlayer->Setup();

	player1Hp = Common::maxHP;
	player2Hp = Common::maxHP;

	collisionlSound.load("jump.mp3");
	downHPSound.load("Right Hook.mp3");
	wallCollisionSound.load("wallcollision.mp3");
	bellSound.load("bell.mp3");
	buzzerSound.load("buzzer.mp3");

	//font
	font.load("bignoodletoo.ttf", 100);
	font2.load("bignoodletoo.ttf", 70);


	isRun = false;
	endSound = true;
}

//--------------------------------------------------------------
void ofApp::update() 
{
	//Tuio
	myTuio.update();

	if (isRun == true)
	{
		//balls update
		int size = balls.size();

		for (int i = 0; i < size; i++)
		{
			balls[i]->update();

			//collision with map
			CollisionBallWithMap(balls[i]);

			if (balls[i]->IstouchedCountNum(3) && !balls[i]->GetDuplicate()) //
			{
				balls[i]->Duplicate();

				//newBall
				Ball* newBall = new Ball(balls[i]->GetPosition(), balls[i]->GetPlayerInfo());
				newBall->setup();
				newBall->SetColor(Ball::ReturnColor(balls[i]->GetPlayerInfo()));
				newBall->SetDirection(balls[i]->GetDirection().x, -balls[i]->GetDirection().y);
				balls.push_back(newBall);
			}
		}

		//touch collision check update
		for (auto& i : inputMap)
		{
			inputDown(i.second);
		}

	}
	else
	{
		if (!endSound)
		{
			buzzerSound.play();
			endSound = true;
		}
		//todo someting
		if ( inputMap.size() > 9  )
		{
			ResetGame();
		}

	}

	//RedPlayer->Update();
	//BluePlayer->Update();

	//frame 
	std::stringstream strm;
	strm << ofGetWidth();
	//strm << "fps: " << ofGetFrameRate();
	//ofSetWindowTitle(strm.str());
	//std::cout << strm << std::endl;	
}

//--------------------------------------------------------------
void ofApp::draw() 
{
	//ofBackgroundGradient(ofColor(255, 50, 0), ofColor(0, 255, 100), OF_GRADIENT_CIRCULAR);
	ofBackground(0, 0, 0);

	//HP Draw
	ofPushMatrix();
	ofSetColor(ofColor::indianRed);
	ofDrawRectangle(0.f, 0.f, (Common::width / 10) * player1Hp, Common::height);
	ofPopMatrix();

	ofPushMatrix();
	ofSetColor(ofColor::blueSteel);
	ofDrawRectangle(Common::width - ((Common::width / 10)*player2Hp), 0.f, Common::width, Common::height);
	ofPopMatrix();

	//Left Line
	ofPushMatrix();
	ofSetColor(ofColor::paleVioletRed);
	ofDrawRectangle(0.f, 0.f, Common::player1area, Common::height);
	ofPopMatrix();

	//Right Line
	ofPushMatrix();
	ofSetColor(ofColor::cadetBlue);
	ofDrawRectangle(Common::player2area, 0.f, Common::width, Common::height);
	ofPopMatrix();

	//Mid Line
	ofPushMatrix();
	ofSetColor(ofColor::black);
	//ofDrawRectangle(Common::width / 2 - 2.f, 0.f, 4.f, Common::height);
	for (int i = 0; i < 10; i++)
	{
		ofDrawRectangle(Common::width - ((Common::width / 10)*i) - 2.0f, 0.f, 4.f, Common::height);
	}
	ofPopMatrix();

	CheckHP();
	

	if (isRun == true)
	{
		//Draw Balls
		for (auto ball : balls)
		{
			//std::cout << balls.size() << std::endl;
			ball->draw();
		}
	}
	else
	{
		if (player1Hp > player2Hp)
		{
			//draw p1 win
			ofPushMatrix();
			ofSetColor(ofColor::red);

			ofPushMatrix();
			ofTranslate(Common::width*0.3, Common::height / 2);
			ofRotate(90);
			font.drawString("p1 win", 0, 0);
			ofPopMatrix();


			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.2, Common::height / 2);
			ofRotate(90);
			font2.drawString("press 5 Finger", 0, 0);
			ofPopMatrix();

			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.1, Common::height / 2);
			ofRotate(90);
			font2.drawString("to start", 0, 0);
			ofPopMatrix();

			ofPopMatrix();



			//draw p2 defeat
			ofPushMatrix();
			ofSetColor(ofColor::blue);

			ofPushMatrix();
			ofTranslate(Common::width * 0.7, Common::height / 2);
			ofRotate(-90);
			font.drawString("p2 defeat", 0, 0);
			ofPopMatrix();


			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.8, Common::height / 2);
			ofRotate(-90);
			font2.drawString("press 5 Finger", 0, 0);
			ofPopMatrix();

			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.9, Common::height / 2);
			ofRotate(-90);
			font2.drawString("to start", 0, 0);
			ofPopMatrix();

			ofPopMatrix();

		}
		else if (player1Hp < player2Hp)
		{
			//draw p2 win
			ofPushMatrix();
			ofSetColor(ofColor::blue);

			ofPushMatrix();
			ofTranslate(Common::width * 0.7, Common::height / 2);
			ofRotate(-90);
			font.drawString("p2 win", 0, 0);
			ofPopMatrix();

			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.8, Common::height / 2);
			ofRotate(-90);
			font2.drawString("press 5 Finger", 0, 0);
			ofPopMatrix();

			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.9, Common::height / 2);
			ofRotate(-90);
			font2.drawString("to start", 0, 0);
			ofPopMatrix();

			ofPopMatrix();

			//////////////////////////////////////////////////////////////////////////
			ofPushMatrix();
			ofSetColor(ofColor::red);

			//draw p1 defeat
			ofPushMatrix();
			ofTranslate(Common::width*0.3, Common::height / 2);
			ofRotate(90);
			font.drawString("p1 defeat", 0, 0);
			ofPopMatrix();

			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.2, Common::height / 2);
			ofRotate(90);
			font2.drawString("press 5 Finger", 0, 0);
			ofPopMatrix();

			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.1, Common::height / 2);
			ofRotate(90);
			font2.drawString("to start", 0, 0);
			ofPopMatrix();

			ofPopMatrix();
		}
		else
		{
			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.8, Common::height / 2);
			ofRotate(-90);
			font2.drawString("press 5 Finger", 0, 0);
			ofPopMatrix();

			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.9, Common::height / 2);
			ofRotate(-90);
			font2.drawString("to start", 0, 0);
			ofPopMatrix();


			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.2, Common::height / 2);
			ofRotate(90);
			font2.drawString("press 5 Finger", 0, 0);
			ofPopMatrix();

			ofPushMatrix();
			ofSetColor(ofColor::purple);
			ofTranslate(Common::width * 0.1, Common::height / 2);
			ofRotate(90);
			font2.drawString("to start", 0, 0);
			ofPopMatrix();
		}

		ofPushMatrix();
		ofSetColor(ofColor::purple);
		ofDrawCircle(Common::width / 2, Common::height / 2, Common::ballRadius);
		ofPopMatrix();
	}


	//RedPlayer->Draw();
	//BluePlayer->Draw();


	//render TUIO Cursors and Objects
	myTuio.drawCursors();
	//myTuio.drawObjects();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) 
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) 
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) 
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) 
{
	//ofPoint touchPoint = ofPoint(x, y);
	//
	//inputDown(touchPoint);

	isRun = false;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) 
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) 
{

}


void ofApp::touchDown(ofTouchEventArgs & touch) 
{
	ofPoint touchPoint = ofPoint(touch.x * Common::width, touch.y * Common::touchheight);

	inputMap.insert( std::make_pair(touch.id, touchPoint) );

	/*
	if (isRun == false)
	{
		float dist = (Common::width / 2 - touchPoint.x)*(Common::width / 2 - touchPoint.x) + (Common::height / 2 - touchPoint.y)*(Common::height / 2 - touchPoint.y);

		if (dist < Common::ballRadius*Common::ballRadius)
		{
			ResetGame();
		}
	}
	*/
}

void ofApp::touchUp(ofTouchEventArgs & touch) 
{
//	ballMap.find(touch.id)->second.setVelocity();
//	ballMap.find(touch.id)->second.stopIncreasing();

	inputMap.erase(touch.id);
}

void ofApp::touchMoved(ofTouchEventArgs & touch) 
{
	//	ofLogNotice("testApp::touchMoved") << " cursor updated: " + ofToString(touch.id) +
	//		" X: " + ofToString(touch.x) +
	//		" Y: " + ofToString(touch.y);

	ofPoint touchPoint = ofPoint(touch.x * Common::width, touch.y * Common::touchheight);

	auto it = inputMap.find(touch.id);
	if (it != inputMap.end())
	{
		it->second = touchPoint;
	}
}

void ofApp::inputDown(ofPoint p)
{
	//auto& b = balls[0];
	for (auto& b : balls)
	{
		//TODO : 터치 범위 수정하기
		if (p.x < Common::player1area)
		{
			//Player1 
			if (Common::PLAYERINFO::Player1 != b->GetPlayerInfo())
			{
				//공 안에 터치포지션이면
				if (b->IsInside(p))
				{
					b->TouchedByPlayer(Common::PLAYERINFO::Player1, p);
					collisionlSound.play();
				}
			}
		}
		else if (p.x > Common::player2area)
		{
			//Player2 
			if (Common::PLAYERINFO::Player2 != b->GetPlayerInfo())
			{
				//공 안에 터치포지션이면
				if (b->IsInside(p))
				{
					b->TouchedByPlayer(Common::PLAYERINFO::Player2, p);
					collisionlSound.play();
				}
			}
		}
	}
}

void ofApp::CollisionBallWithMap(Ball* b)
{
	//가로 충돌
	if (b->GetPosition().y + Common::ballRadius > Common::height || b->GetPosition().y - Common::ballRadius < 0.f)
	{
		b->SetDirection(b->GetDirection().x, -b->GetDirection().y);
		wallCollisionSound.play();
	}

	//오른쪽 세로 충돌
	if (b->GetPosition().x + Common::ballRadius > Common::width)
	{
		b->SetDirection(-b->GetDirection().x, b->GetDirection().y);
		b->SetPosition( ofPoint(b->position.x + b->direction.x, b->position.y + b->direction.y) );
		b->ChangePlayerInfo();
		b->SetColor(b->ReturnColor(b->GetPlayerInfo()));
		player2Hp--;
		downHPSound.play();
	}

	//왼쪽 세로 충돌
	if (b->GetPosition().x - Common::ballRadius < 0.f)
	{
		b->SetDirection(-b->GetDirection().x, b->GetDirection().y);
		b->SetPosition(ofPoint(b->position.x + b->direction.x, b->position.y + b->direction.y));
		b->ChangePlayerInfo();
		b->SetColor(b->ReturnColor(b->GetPlayerInfo()));
		player1Hp--;
		downHPSound.play();
	}
}

void ofApp::CheckHP()
{
	if (player1Hp <= 0)
	{
		ofPushMatrix();
		ofSetColor(ofColor::blue);
		ofDrawCircle(Common::width/2, Common::height/2, 50.f);
		ofPopMatrix();

		isRun = false;
	}

	if (player2Hp <= 0)
	{
		ofPushMatrix();
		ofSetColor(ofColor::red);
		ofDrawCircle(Common::width/2, Common::height/2, 50.f);
		ofPopMatrix();

		isRun = false;
	}
}

void ofApp::ResetGame()
{
	if (isRun == false)
	{
		inputMap.clear();
		balls.clear();

		//New Ball
		Ball* newBall = new Ball(Common::width/2, Common::height/2, Common::PLAYERINFO::Player1);
		newBall->setup();
		newBall->SetColor(ofColor::purple);
		//newBall->SetPlayerInfo(Common::PLAYERINFO::Player1);
		balls.push_back(newBall);

		player1Hp = Common::maxHP;
		player2Hp = Common::maxHP;

		isRun = true;
		endSound = false;

		bellSound.play();
	}
}

