#include "EntityManager.h"
#include "TransformComponent.h"

namespace ph { namespace entity {

	EntityManager::EntityManager()
		: m_LastID(INVALID_ENTITY) {
	}

	EntityManager::~EntityManager() {
		for (uint i = 0; i < m_Entities.size(); i++) {
			delete m_Entities[i];
		}
		m_Entities.clear();
	}

	void EntityManager::Add(Entity* entity) {
		if (m_AvailableIDs.empty()) {
			PH_ASSERT(m_LastID < MAX_ENTITY_ID, "Maximum number of entities reached!");
			entity->SetID(++m_LastID);
		}
		else {
			EntityID freeID = m_AvailableIDs.front();
			m_AvailableIDs.pop();
			entity->SetID(freeID);
		}
		
		m_Entities.push_back(entity);
		if (!entity->GetComponent<TransformComponent>()) {
			PH_WARN("Entity does not have transform! Creating...");
			entity->AddComponent(new TransformComponent(math::Mat4::Identity()));
		}
	}

	Entity* EntityManager::Remove(Entity* entity) {
		for (uint i = 0; i < m_Entities.size(); i++) {
			if (m_Entities[i]->GetID() == entity->GetID()) {
				Entity* e = entity;
				m_Entities.erase(m_Entities.begin() + i);
				return e;
			}
		}
		return nullptr;
	}

}}