#include "ofMain.h"
#include "Ball.h"
#include <stdlib.h>
#include <math.h>

Ball::Ball()
{

}

Ball::Ball(float x, float y) : position(ofPoint(x, y))
{
}


Ball::Ball(ofPoint point) : position(point)
{

}

Ball::Ball(float x, float y, ofColor c) : position(ofPoint(x, y)), color(c)
{

}

Ball::Ball(float x, float y, Common::PLAYERINFO pinfo) : position(ofPoint(x, y)), playerInfo(pinfo)
{

}

Ball::Ball(ofPoint p, Common::PLAYERINFO pinfo) : position(p), playerInfo(pinfo)
{
}

Ball::~Ball()
{

}

void Ball::setup()
{
	radius = Common::ballRadius;
	speed = ofPoint(Common::testspeed_x, Common::testspeed_y);
	SetUpDirection();
	touchedCount = 0;
}

void Ball::update()
{
	//color = ReturnColor(playerInfo);

	//벽하고 충돌 검사
	//CollisionWithMap();

	//속력 변화
	//AutoChangeSpeed();
	//AutoChangeSpeedByLevel();

	//이동
	position.x += direction.x * speed.x * ofGetLastFrameTime();
	position.y += direction.y * speed.y * ofGetLastFrameTime();

	//잔상 처리
	if (afterimg.size() >= Common::afterimgSize)
	{
		afterimg.pop_front();
	}
	afterimg.push_back(position);
}

void Ball::draw()
{
	//잔상
	ofPushMatrix();
	for (auto& i : afterimg)
	{
		ofNoFill();
		//ofSetColor( ofColor(color.r, color.g, color.b, i/afterimg.size()) );
		ofSetColor(color);
		ofDrawCircle(i, radius);
		ofFill();
	}
	ofPopMatrix();

	ofPushMatrix();

	ofSetColor(color);
	ofDrawCircle(position, radius);
	
	ofPopMatrix();
}

ofColor Ball::ReturnColor(Common::PLAYERINFO pin)
{
	switch (pin)
	{
	case Common::PLAYERINFO::NONE:
	{
		return ofColor::purple;
	}
	case Common::PLAYERINFO::Player1:
	{
		return ofColor::red;
	}
	case Common::PLAYERINFO::Player2:
	{
		return ofColor::blue;
	}
	default:
		return ofColor::pink;
		break;
	}
}

void Ball::CollisionWithMap()
{	
	if (position.y + radius > Common::height || position.y - radius < 0.f)
	{
		direction.y = -direction.y;
	}

	//TODO : TEST CODE
	if (position.x + radius > Common::width)
	{
		direction.x = -direction.x;
		ChangePlayerInfo();
	}
	if (position.x - radius < 0.f)
	{
		direction.x = -direction.x;
		ChangePlayerInfo();
	}
}

void Ball::AutoChangeSpeed()
{
	speed.x *= Common::increaseSpeed;
	speed.y *= Common::increaseSpeed;
}

void Ball::AutoChangeSpeedByLevel()
{
	//TODO
	if (touchedCount      <  2)
	{
		speed.x = Common::speedlevel1;
	}
	else if (touchedCount < 3 )
	{
		speed.x = Common::speedlevel2;
	}
	else if (10 <= touchedCount < 15)
	{
		speed.x = Common::speedlevel3;
	}
	else
	{
		speed.x = Common::speedlevel4;
	}
}

void Ball::TouchedByPlayer(Common::PLAYERINFO pinfo, ofPoint p)
{
	if (p.y < position.y)
	{
		direction.y = 1.f;
	}
	else
	{
		direction.y = -1.f;
	}

	direction.x *= -1;

	//TODO : YSPEED
	speed.x = ofRandom(3.f, 12.f) * 100.f;  
	speed.y = ofRandom(2.f, 10.f) * 100.f;

	ChangePlayerInfo();
	SetColor(ReturnColor(pinfo));

	touchedCount++;
}

bool Ball::IsInside(ofPoint touchPoint)
{
	if (touchPoint.x > (position.x - Common::ballRadiusReal) &&
		touchPoint.x < (position.x + Common::ballRadiusReal) &&
		touchPoint.y >(position.y - Common::ballRadiusReal) &&
		touchPoint.y < (position.y + Common::ballRadiusReal))
	{
		return true;
	}

	return false;
}

bool Ball::IstouchedCountNum(int num)
{
	return touchedCount == num ? true : false;
}

void Ball::SetUpDirection()
{
	if (playerInfo == Common::PLAYERINFO::Player1)
	{
		direction = ofPoint(1.f, 1.f);
	} 
	else if(playerInfo == Common::PLAYERINFO::Player2)
	{
		direction = ofPoint(-1.f, -1.f);
	}
}

void Ball::ChangePlayerInfo()
{
	switch (playerInfo)
	{
	case Common::PLAYERINFO::Player1:
		playerInfo = Common::PLAYERINFO::Player2;
		break;
	case Common::PLAYERINFO::Player2:
		playerInfo = Common::PLAYERINFO::Player1;
		break;
	default:
		break;
	}
}

void Ball::Duplicate()
{
	isDuplicated = true;
}
