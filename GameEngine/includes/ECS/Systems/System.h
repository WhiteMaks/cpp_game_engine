#pragma once

namespace ECS
{

	class System
	{
	public:
		virtual void Init() noexcept;
		virtual void Update() noexcept;
		virtual void Render() noexcept;
		virtual void Destroy() noexcept;
	};

}