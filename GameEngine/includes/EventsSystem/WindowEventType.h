#pragma once

namespace EventsSystem
{

	enum class WindowEventType
	{
		CLOSE, //if close button is pressed
		RESIZE, //if window size changed

		INVALID //if event is invalid
	};

}