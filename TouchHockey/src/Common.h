#pragma once
#include "ofMain.h"
/*	coordinate
	0,0				+





	+				++
*/

namespace Common
{
	enum class PLAYERINFO
	{
		NONE = 0,
		Player1 = 1,
		Player2 = -1
	};

	//1920 1200
	//1280 1080
	constexpr float width = 1920;
	constexpr float height = 1120; //1120
	constexpr float touchheight = 1000;
	constexpr float mid = width / 2;

	constexpr float goalarea = width / 10;
	constexpr float player1area = 0 + goalarea;
	constexpr float player2area = width - goalarea;

	constexpr float ballRadius = 55.0f;
	constexpr float ballRadiusReal = 65.0f;

	constexpr float testspeed_x = 500.f;
	constexpr float testspeed_y = 200.f;
	constexpr float increaseSpeed = 1.00f;

	constexpr float speedlevel1 = 300.0f;
	constexpr float speedlevel2 = 600.0f;
	constexpr float speedlevel3 = 900.0f;
	constexpr float speedlevel4 = 1200.0f;

	constexpr int	afterimgSize = 7;

	constexpr float barSize = 100.f;

	constexpr int	maxHP = 5;
}
