#include "ofMain.h"
#include "Bar.h"
#include <stdlib.h>
#include <math.h>
#include "Common.h"

Bar::Bar()
{

}

Bar::~Bar()
{
}

void Bar::Setup()
{
	barSize = Common::barSize;
}

void Bar::Update()
{

}

void Bar::Draw()
{
	ofDrawLine(ofPoint(mid.x, mid.y - barSize), ofPoint(mid.x, mid.y + barSize));
}

void Bar::SetMid(ofPoint p)
{
	mid = p;
}
