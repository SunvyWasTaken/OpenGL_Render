// SunvyNeverExist Copyright please don't steal work that isn't yours

#pragma once

#include "Component.h"
#include "Transform.h"

namespace Lite
{
	class Entity;

	// Component that is gonna be use for all renderable component Like for shape and more.
	class LITE_API RenderableComponent : public IComponent
	{
	public:

		explicit RenderableComponent(Entity* owner = nullptr);

		virtual void TickComponent(const float Deltatime) override;

		/************************************************************************/
		/* Simple Getter for Transform                                          */
		/************************************************************************/

		FVector GetComponentLocation() const;

		FVector GetLocationOffset() const;

		FVector GetComponentSize() const;

		FVector GetSizeOffset() const;

		/************************************************************************/
		/* Setter for All Transform												*/
		/************************************************************************/

		virtual void SetLocationOffset(const FVector& NewLocation);

		virtual void SetSizeOffset(const FVector& NewSize);

	private:

		FTransform m_ComponentTransform;

	};
}
