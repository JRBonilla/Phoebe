#include <Phoenix.h>

#define TEST_RENDERING 1

#if TEST_RENDERING
#define TEST_BATCH_RENDER 1

int main(int argc, char* args[]) {
	using namespace ph;
	using namespace math;
	using namespace audio;
	using namespace graphics;
	using namespace debug;

	Window window("Phoenix Sandbox", 1152, 648);
	mat4 projectionMatrix = mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
	Layer* test2D = new Layer(new Renderer, ShaderManager::Get("default"), projectionMatrix);
	
	srand(time(nullptr));

#if TEST_BATCH_RENDER
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
#else
	Texture* texture1 = new Texture("res/test.png");
	Texture* texture2 = new Texture("res/test2.png");
	test2D->Add(new Sprite(4.0f, 4.0f, 2.0f, 2.0f, texture2));
	test2D->Add(new Sprite(-4.0f, -4.0f, 2.0f, 2.0f, texture1));
#endif

	DebugInfoLayer debug;
	debug.Init();

	int textureIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

	ShaderManager::Get("default")->Enable();
	ShaderManager::Get("default")->SetUniform1iv("textures", PHOENIX_LEN(textureIDs), textureIDs);

	double currentFrame = Timer::GetInstance()->Elapsed();
	double lastFrame = currentFrame;
	double deltaTime;

	// Game loop
	while (!window.Closed()) {
		// Update
		window.Update();
		debug.Update();
		test2D->Update();
		window.ClearBuffer();

		// Set light position
		ShaderManager::Get("default")->Enable();
		vec2 light_position = vec2(InputManager::GetInstance().GetMouseX() * 32.0f / window.GetWidth() - 16.0f, 9.0f - InputManager::GetInstance().GetMouseY() * 18.0f / window.GetHeight());
		ShaderManager::Get("default")->SetUniform2f("light_position", light_position);

		currentFrame = Timer::GetInstance()->Elapsed();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Camera
		if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_LEFT)) {
			test2D->GetCamera()->Translate(6.0f * deltaTime, 0.0f, 0.0f);
		}
		else if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_RIGHT)) {
			test2D->GetCamera()->Translate(-6.0f * deltaTime, 0.0f, 0.0f);
		}
		if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_UP)) {
			test2D->GetCamera()->Translate(0.0f, -6.0f * deltaTime, 0.0f);
		}
		else if (InputManager::GetInstance().IsKeyPressed(GLFW_KEY_DOWN)) {
			test2D->GetCamera()->Translate(0.0f, 6.0f * deltaTime, 0.0f);
		}

		// Render
		if (test2D->IsVisible()) test2D->Render();
		if (debug.IsVisible()) debug.Render();
		window.SwapBuffers();
	}

	delete texture1;
#if TEST_BATCH_RENDER
	delete texture2;
#endif
	delete test2D;
	return 0;
}
#else
int main(int argc, char* args[]) {
	ph::Window window("Phoenix Sandbox", 1152, 648);
	
	while (!window.Closed()) {
		window.Update();
		window.ClearBuffer();
		window.SwapBuffers();
	}
	return 0;
}
#endif