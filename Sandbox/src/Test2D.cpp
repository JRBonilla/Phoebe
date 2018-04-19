#include "Test2D.h"
#include <random>
#include <time.h>
#include <ph/renderer/shaders/ShaderManager.h>
#include <ph/app/InputManager.h>
#include <ph/app/Application.h>

using namespace ph;
using namespace math;
using namespace renderer;

Test2D::Test2D()
	: Layer2D(ShaderManager::Get("Basic2D"), Mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)) {
}

Test2D::~Test2D() {
	delete m_CrateTexture;
}

void Test2D::Init() {
	Layer2D::Init();
	srand(time(nullptr));

	ShaderManager::Add(this->GetShader());

	m_CrateTexture = new Texture2D("crate", "res/crate.png");
	for (float x = -16.0f; x < 16.0f; x++) {
		int randNum = (rand() % 2) + 1;
		for (float y = -9.0f; y < 9.0f; y++) {
			Add(new Sprite(x, y, 0.9f, 0.9f, m_CrateTexture));
		}
	}

	int textureIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

	ShaderManager::Get("Basic2D")->Bind();
	ShaderManager::Get("Basic2D")->SetUniform("textures", (byte*)&textureIDs);

	RenderSystem::SetDepthTesting(false);
	RenderSystem::SetFaceCulling(false);
}

void Test2D::Update() {
	Layer2D::Update();

	ShaderManager::Get("Basic2D")->Bind();
	Vec2 light_position = Vec2(
		InputManager::GetMouseX() * 32.0f / Application::GetApplication().GetWindow()->GetWidth() - 16.0f,
		9.0f - InputManager::GetMouseY() * 18.0f / Application::GetApplication().GetWindow()->GetHeight());
	ShaderManager::Get("Basic2D")->SetUniform("light_position", (byte*)&light_position);


	if (InputManager::IsKeyPressed(GLFW_KEY_LEFT) || InputManager::IsKeyPressed(GLFW_KEY_A)) {
		GetCamera()->Translate(1.0f, 0.0f, 0.0f);
	}
	else if (InputManager::IsKeyPressed(GLFW_KEY_RIGHT) || InputManager::IsKeyPressed(GLFW_KEY_D)) {
		GetCamera()->Translate(-1.0f, 0.0f, 0.0f);
	}

	if (InputManager::IsKeyPressed(GLFW_KEY_UP) || InputManager::IsKeyPressed(GLFW_KEY_W)) {
		GetCamera()->Translate(0.0f, -1.0f, 0.0f);
	}
	else if (InputManager::IsKeyPressed(GLFW_KEY_DOWN) || InputManager::IsKeyPressed(GLFW_KEY_S)) {
		GetCamera()->Translate(0.0f, 1.0f, 0.0f);
	}
}