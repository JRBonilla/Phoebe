#include "Flow.h"

int main(int argc, char* args[])
{
	using namespace fl;
	using namespace math;
	using namespace audio;
	using namespace graphics;
	using namespace debug;

	Window window("Flow Engine", 960, 540, false, true );
	Shader shader("res/shaders/default/default.vert", "res/shaders/default/default.frag");

	Layer* test2D = new Layer(new Renderer, &shader, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	srand(time(nullptr));
	
	Texture* texture1 = new Texture("res/test.png");
	Texture* texture2 = new Texture("res/test2.png");
	for (float x = -16.0f; x < 16.0f; x++) {
		int randNum = (rand() % 2) + 1;
		for (float y = -9.0f; y < 9.0f; y++) {
			if (randNum % 2 == 0) {
				test2D->Add(new Sprite(x, y, 0.9f, 0.9f, texture1));
			}
			else {
				test2D->Add(new Sprite(x, y, 0.9f, 0.9f, texture2));
			}
		}
	}

	DebugLayer debugLayer(window.GetGLFWWindow());
	debugLayer.Init();
	
	int textureIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

	shader.Enable();
	shader.SetUniform1iv("textures", LEN(textureIDs), textureIDs);

	double currentFrame = Timer::GetInstance()->Elapsed();
	double lastFrame = currentFrame;
	double deltaTime;

	// Game loop
	while (!window.Closed()) {
		// Update
		window.Update();
		debugLayer.Update();
		test2D->Update();
		window.ClearBuffer();

		// Set light position
		shader.Enable();
		shader.SetUniform2f("light_pos", vec2(InputManager::GetInstance().GetMouseX() * 32.0f / window.GetWidth() - 16.0f, 9.0f - InputManager::GetInstance().GetMouseY() * 18.0f / window.GetHeight()));

		currentFrame = Timer::GetInstance()->Elapsed();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Camera
		if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_LEFT)) {
			test2D->GetCamera()->Translate( 6.0f * deltaTime, 0.0f, 0.0f);
		}
		else if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_RIGHT)) {
			test2D->GetCamera()->Translate(-6.0f * deltaTime, 0.0f, 0.0f);
		}
		if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_UP)) {
			test2D->GetCamera()->Translate(0.0f, -6.0f * deltaTime, 0.0f);
		}
		else if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_DOWN)) {
			test2D->GetCamera()->Translate(0.0f,  6.0f * deltaTime, 0.0f);
		}

		// Render
		if (test2D->IsVisible()) test2D->Render();
		if (debugLayer.IsVisible()) debugLayer.Render();
		window.SwapBuffers();
	}

	delete texture1;
	delete texture2;
	delete test2D;
	return 0;
}