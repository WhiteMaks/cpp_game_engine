#pragma once

namespace GameEngine
{

	enum MouseEventType
	{
		L_PRESS, //if left key is pressed
		L_RELEASE, //if left key is released

		R_PRESS, //if right key is pressed
		R_RELEASE, //if right key is released

		WHEEL_UP, //if wheel scroll up
		WHEEL_DOWN, //if wheel scroll down

		MOVE, //if position changed
		ENTER,
		LEAVE,

		INVALID //if event is invalid
	};

}