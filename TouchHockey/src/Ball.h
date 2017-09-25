#pragma once
#include "Common.h"
#include <deque>

class Ball //: ofBaseApp
{
public:
	Ball();
	Ball(float x, float y);
	Ball(ofPoint point);
	Ball(float x, float y, ofColor c);
	Ball(float x, float y, Common::PLAYERINFO pinfo);
	Ball(ofPoint p, Common::PLAYERINFO pinfo);
	~Ball();

public:
	void						setup();
    void						update();
    void						draw();

	//Getter
	inline ofPoint				GetPosition() { return position; };
	inline Common::PLAYERINFO	GetPlayerInfo() { return playerInfo; };
	inline ofPoint				GetDirection() { return direction; };
	inline bool					GetDuplicate() { return isDuplicated; };

	//Setter
	inline void					Setid(int tuioID) { id = tuioID; };
	inline void					SetPlayerInfo(Common::PLAYERINFO pinfo) { playerInfo = pinfo; };
	inline void					SetColor(ofColor c) { color = c; };
	inline void					SetDirection(ofPoint d) { direction = d; };
	inline void					SetPosition(ofPoint p) { position = p; };
	inline void					SetDirection(float x, float y) { direction = ofPoint(x, y); };

	
	void						AutoChangeSpeed(); //충돌이 일어날 시 속도를 높혀줍니다.
	void						AutoChangeSpeedByLevel(); //충돌이 일어날 시 레벨에 따라서 속도를 높혀줍니다.
	void						TouchedByPlayer(Common::PLAYERINFO pinfo, ofPoint p);
	bool						IsInside(ofPoint touchPoint);
	bool						IstouchedCountNum(int num);
	void						Duplicate();

	static ofColor				ReturnColor(Common::PLAYERINFO pin);

	void						ChangePlayerInfo();
	
private:
	int							id;
	void						SetUpDirection();

	void						CollisionWithMap();
	std::deque<ofPoint>			afterimg;

public:
	ofPoint						position;
	ofPoint						direction;
	int							touchedCount;
private:
	float						radius;

	ofPoint						speed;


	ofColor						color;

	Common::PLAYERINFO			playerInfo;

	bool						isDuplicated = false;
};

