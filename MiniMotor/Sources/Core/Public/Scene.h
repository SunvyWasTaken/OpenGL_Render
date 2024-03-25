// SunvyNeverExist Copyright please don't steal work that isn't yours

#pragma once

#include "Core.h"

#include <memory>
#include <vector>

namespace Lite
{
	class Entity;

	class LITE_API Scene
	{
	public:
		Scene();
		virtual ~Scene();

	private:
		//std::vector<std::unique_ptr<Entity>> EntirtyList;
	};
}
	
