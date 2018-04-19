#pragma once

#include <vector>
#include "Light.h"
#include "ph/Types.h"

namespace ph { namespace renderer {

	class LightSetup {
	private:
		std::vector<Light*> m_Lights;
	public:
		LightSetup();
		~LightSetup();

		void Add(Light* light);
		void Remove(Light* light);

		inline const std::vector<Light*>& GetLights() const { return m_Lights; }
	};

	typedef std::vector<LightSetup*> LightSetupStack;

}}