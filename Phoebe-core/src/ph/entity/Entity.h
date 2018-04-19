#pragma once

#include <unordered_map>
#include "Component.h"
#include "ph/Types.h"
#include "ph/utils/Log.h"

namespace ph { namespace entity {

	typedef uint EntityID;
	static const EntityID MAX_ENTITY_ID  = (std::numeric_limits<EntityID>::max)();
	static const EntityID INVALID_ENTITY = (EntityID)0;

	typedef std::unordered_map<ComponentType*, Component*> ComponentMap;

	class Entity {
	protected:
		friend class EntityManager;

		EntityID      m_ID;
		ComponentMap  m_Components;
	public:
		Entity() : m_ID(INVALID_ENTITY) {}

		inline void AddComponent(Component* component) {
			PH_ASSERT(component->GetType(), "Component does not have a type!");
			m_Components[component->GetType()] = component;
		}

		template <typename T>
		const T* GetComponent() const {
			return GetComponentInternal<T>();
		}

		template <typename T>
		T* GetComponent() {
			return (T*)GetComponentInternal<T>();
		}

		inline EntityID GetID() const { return m_ID; }
	private:
		inline void SetID(EntityID id) { m_ID = id; }

		template <typename T>
		const T* GetComponentInternal() const {
			ComponentType* type = T::GetStaticType();
			auto it = m_Components.find(type);
			if (it == m_Components.end()) {
				return nullptr;
			}
			return (T*)it->second;
		}
	};

}}