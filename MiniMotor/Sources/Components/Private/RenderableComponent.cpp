// SunvyNeverExist Copyright please don't steal work that isn't yours

#include "RenderableComponent.h"

#include "Entity.h"

namespace Lite
{
	RenderableComponent::RenderableComponent(Entity* owner /* = nullptr */) : IComponent(owner)
	{

	}

	void RenderableComponent::TickComponent(const float Deltatime)
	{
	}

	FVector RenderableComponent::GetComponentLocation() const
	{
		if (GetOwner() != nullptr)
		{
			return GetOwner()->GetEntityLocation() + GetLocationOffset();
		}
		return GetLocationOffset();
	}

	FVector RenderableComponent::GetLocationOffset() const
	{
		return m_ComponentTransform.Location;
	}

	FVector RenderableComponent::GetComponentSize() const
	{
		if (GetOwner() != nullptr)
		{
			return GetOwner()->GetEntitySize() * GetSizeOffset();
		}
		return GetSizeOffset();
	}

	FVector RenderableComponent::GetSizeOffset() const
	{
		return m_ComponentTransform.Scale;
	}

	void RenderableComponent::SetLocationOffset(const FVector& NewLocation)
	{
		m_ComponentTransform.Location = NewLocation;
	}

	void RenderableComponent::SetSizeOffset(const FVector& NewSize)
	{
		m_ComponentTransform.Scale = NewSize;
	}

}
