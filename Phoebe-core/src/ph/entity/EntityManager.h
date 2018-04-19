#pragma once

#include <queue>
#include "Entity.h"
#include "ph/Types.h"

namespace ph { namespace entity {

	typedef std::vector<Entity*> EntityList;
	typedef std::queue<EntityID> EntityIDQueue;

	class EntityManager {
	private:
		EntityList     m_Entities;
		EntityID       m_LastID;
		EntityIDQueue  m_AvailableIDs;
	public:
		EntityManager();
		~EntityManager();

		void Add(Entity* entity);
		Entity* Remove(Entity* entity);

		inline const EntityList&    GetEntities()     const { return m_Entities; }
		inline const EntityIDQueue& GetAvailableIDs() const { return m_AvailableIDs; }
	};

}}