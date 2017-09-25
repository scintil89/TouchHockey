#pragma once
#include "Common.h"

class Bar //: ofBaseApp
{
public:
	Bar();
	~Bar();

	void Setup();
	void Update();
	void Draw();
	void SetMid(ofPoint p);

private:
	ofPoint		mid;
	float		barSize;

};

