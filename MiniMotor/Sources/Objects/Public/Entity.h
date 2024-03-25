// SunvyNeverExist Copyright please don't steal work that isn't yours

#pragma once

#include "Object.h"
#include "Component.h"
#include "Transform.h"

#include <memory>
#include <vector>

namespace Lite
{
	class IComponent;

	class LITE_API Entity : public IObject
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void BeginPlay();

		virtual void Tick(float deltatime);

		//template <typename T>
		//T* CreateComponent()
		//{
		//	if constexpr (!std::is_class_v<T> || !std::is_base_of_v<IComponent, T>)
		//	{
		//		throw "Component given to the CreateComponent isn't a child of IComponent";
		//	}
		//	T* NewObject = new T(this);
		//	//ComponentsList.push_back(std::make_unique<T>(NewObject));
		//	return NewObject;
		//}

		/************************************************************************/
		/* Getter Location														*/
		/************************************************************************/

		FVector GetEntityLocation() const;

		FRotator GetEntityRotation() const;

		FVector GetEntitySize() const;

		FTransform GetEntityTransform() const;

		virtual void SetEntityLocation(const FVector& NewLocation);

		virtual void SetEntityRotation(const FRotator& NewRotation);

		virtual void SetEntitySize(const FVector& NewSize);

		virtual void SetEntityTransform(const FTransform& NewTransform);

	private:
		/************************************************************************/
		/* Components                                                           */
		/************************************************************************/
		//std::vector<std::unique_ptr<IComponent>> ComponentsList;

		/************************************************************************/
		/* Location                                                             */
		/************************************************************************/
		FTransform m_Transform;
	};
}