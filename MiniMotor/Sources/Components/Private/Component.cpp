// SunvyNeverExist Copyright please don't steal work that isn't yours

#include "Component.h"

#include "Entity.h"

namespace Lite
{
	IComponent::IComponent(Entity* owner /* = nullptr */) : IObject(), m_Owner(owner)
	{
	}

	IComponent::~IComponent()
	{

	}

	void IComponent::TickComponent(const float Deltatime)
	{
		
	}
}
