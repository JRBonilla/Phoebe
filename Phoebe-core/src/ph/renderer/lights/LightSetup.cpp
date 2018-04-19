#include "LightSetup.h"

namespace ph { namespace renderer {

	LightSetup::LightSetup() {}

	LightSetup::~LightSetup() {
		for (uint i = 0; i < m_Lights.size(); i++) {
			delete m_Lights[i];
		}
		m_Lights.clear();
	}

	void LightSetup::Add(Light* light) {
		m_Lights.push_back(light);
	}

	void LightSetup::Remove(Light* light) {
		for (uint i = 0; i < m_Lights.size(); i++) {
			if (m_Lights[i] == light) {
				m_Lights.erase(m_Lights.begin() + i);
				break;
			}
		}
	}

}}