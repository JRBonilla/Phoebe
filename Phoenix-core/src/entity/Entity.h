#pragma once

namespace ph { namespace entity {

	typedef unsigned int EntityID;
	static const EntityID INVALID_ENTITYID = (EntityID)0;

	class Entity {
	private:
		EntityID m_EntityID;
	public:
		Entity() : m_EntityID(INVALID_ENTITYID) { }
		Entity(EntityID id) : m_EntityID(id) { }

		inline EntityID GetID() const { return m_EntityID; }
		inline void SetID(EntityID id) { m_EntityID = id; }
	};

}}