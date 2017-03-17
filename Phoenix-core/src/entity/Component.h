#pragma once

#include <cstddef>
#include "Entity.h"

namespace ph { namespace entity {

	typedef unsigned int ComponentID;
	typedef std::size_t ComponentType;
	static const ComponentType INVALID_COMPONENTTYPE = 0;

	class Component {
	private:
		Entity* m_Entity;
	public:
		inline Entity* GetEntity() const { return m_Entity; }
		inline void SetEntity(Entity* entity) { m_Entity = entity; }
		inline const ComponentType GetType() const { return INVALID_COMPONENTTYPE; }
	};

}}