#pragma once

#include <ph/renderer/Layer2D.h>
#include <ph/renderer/renderables/Sprite.h>

class Test2D : public ph::renderer::Layer2D {
private:
	ph::renderer::Texture2D* m_CrateTexture;
public:
	Test2D();
	~Test2D();

	void Init() override;
	void Update() override;
};