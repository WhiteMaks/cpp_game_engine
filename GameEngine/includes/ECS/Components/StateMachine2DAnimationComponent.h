#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Core/Core.h"

#include "Component.h"
#include "Core/GraphicsEngine/Library/Sprite.h"
#include "Tools/Time.h"

namespace ECS
{
	struct GAME_ENGINE_API Frame2DAnimation
	{
		std::shared_ptr<GraphicsEngine::Sprite> sprite;
		int time;
	};

	class GAME_ENGINE_API State2DAnimation
	{
	private:
		std::string name;
		std::vector<Frame2DAnimation> frames;

		unsigned int currentFrameIndex;
		int timeTracker;

	public:
		State2DAnimation(const std::string& name) noexcept
			: name(name), currentFrameIndex(0), timeTracker(0)
		{
		}

	public:
		void AddFrame(const Frame2DAnimation& frame) noexcept
		{
			frames.push_back(frame);
		}

		void Update() noexcept
		{
			timeTracker -= GameEngine::Time::GetDeltaTime();

			if (timeTracker < 0)
			{
				currentFrameIndex++;

				if (currentFrameIndex >= frames.size())
				{
					currentFrameIndex = 0;
				}

				timeTracker = frames[currentFrameIndex].time;
			}
		}

		Frame2DAnimation& GetCurrentFrame() noexcept
		{
			return frames[currentFrameIndex];
		}

		std::string& GetName() noexcept
		{
			return name;
		}
	};

	struct GAME_ENGINE_API StateMachine2DAnimationComponent : public Component
	{
		std::vector<State2DAnimation> states;
		State2DAnimation* currentState;

		void Play(std::string& stateName) noexcept
		{
			if (currentState != nullptr && currentState->GetName() == stateName)
			{
				return;
			}

			for (State2DAnimation state : states)
			{
				if (state.GetName() == stateName)
				{
					currentState = &state;
					break;
				}
			}
		}

	};

}