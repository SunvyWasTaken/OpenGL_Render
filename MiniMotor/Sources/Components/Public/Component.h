// SunvyNeverExist Copyright please don't steal work that isn't yours

#pragma once

#include "Object.h"

namespace Lite
{
	class Entity;

	class LITE_API IComponent : public IObject
	{
	public:
		
		explicit IComponent(Entity* owner = nullptr);

		virtual ~IComponent() override;

		virtual void TickComponent(const float Deltatime);

		Entity* GetOwner() const { return m_Owner; }

		template <typename OwnerType>
		OwnerType* GetOwner() const
		{
			return (m_Owner ? (OwnerType*)m_Owner : nullptr);
		}

	private:
		Entity* m_Owner;
	};
}
