#pragma once

#include <string>

namespace ph { namespace entity {

	class Entity;
	
	struct ComponentType {
		std::string name;
	};

	class Component {
	protected:
		Entity* m_Entity;
	public:
		virtual ComponentType* GetType()   const { return nullptr; }
		virtual Entity*        GetEntity() const { return m_Entity; }
	};

}}