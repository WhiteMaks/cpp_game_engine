#pragma once

#include <memory>

#include "Keyboard.h"
#include "Mouse.h"
#include "Window.h"
#include "Tools/Log.h"
#include "Core/Core.h"

namespace EventsSystem
{

	class GAME_ENGINE_API EventManager
	{
	private:
		static EventManager* instance;

		Mouse* mouse;
		Keyboard* keyboard;
		Window* window;

	public:
		static int keyA;
		static int keyB;
		static int keyC;
		static int keyD;
		static int keyE;
		static int keyF;
		static int keyG;
		static int keyH;
		static int keyI;
		static int keyJ;
		static int keyK;
		static int keyL;
		static int keyM;
		static int keyN;
		static int keyO;
		static int keyP;
		static int keyQ;
		static int keyR;
		static int keyS;
		static int keyT;
		static int keyU;
		static int keyV;
		static int keyW;
		static int keyX;
		static int keyY;
		static int keyZ;

	public:
		~EventManager() = delete;

		EventManager(EventManager& other) = delete;

		void operator=(const EventManager& ev) = delete;

	private:
		EventManager() noexcept;

	public:
		static EventManager* GetInstance() noexcept;

		void Init() noexcept;
		void Destroy() noexcept;

		Mouse* GetMouse() const noexcept;
		Keyboard* GetKetboard() const noexcept;
		Window* GetWindow() const noexcept;

	};

}