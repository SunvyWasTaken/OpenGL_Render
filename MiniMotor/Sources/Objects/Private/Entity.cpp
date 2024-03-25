// SunvyNeverExist Copyright please don't steal work that isn't yours

#include "Entity.h"
#include "Component.h"

namespace Lite
{
	Entity::Entity() : IObject()
	{
	}

	Entity::~Entity()
	{
		
	}

	void Entity::BeginPlay()
	{
	}

	void Entity::Tick(float deltatime)
	{
		//for (auto& comp : ComponentsList)
		//{
		//	comp->TickComponent(deltatime);
		//}
	}

	/************************************************************************/
	/* Location / Transformation Spot                                       */
	/************************************************************************/

	FVector Entity::GetEntityLocation() const
	{
		return m_Transform.Location;
	}

	FRotator Entity::GetEntityRotation() const
	{
		return m_Transform.Rotation;
	}

	FVector Entity::GetEntitySize() const
	{
		return m_Transform.Scale;
	}

	FTransform Entity::GetEntityTransform() const
	{
		return m_Transform;
	}

	void Entity::SetEntityLocation(const FVector& NewLocation)
	{
		m_Transform.Location = NewLocation;
	}

	void Entity::SetEntityRotation(const FRotator& NewRotation)
	{
		m_Transform.Rotation = NewRotation;
	}

	void Entity::SetEntitySize(const FVector& NewSize)
	{
		m_Transform.Scale = NewSize;
	}

	void Entity::SetEntityTransform(const FTransform& NewTransform)
	{
		m_Transform = NewTransform;
	}

}
