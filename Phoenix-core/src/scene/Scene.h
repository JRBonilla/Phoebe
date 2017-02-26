#pragma once

#include <vector>
#include "../layers/Layer.h"

namespace ph { namespace scene {

	class Scene {
	private:
		std::vector<graphics::Layer*> m_Layers;
	public:
		Scene();
		~Scene();

		void Init();

		void PushLayer(graphics::Layer* layer);
		void PopLayer();
	};

}}