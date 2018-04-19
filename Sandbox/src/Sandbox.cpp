#include <ph/app/Application.h>
#include "Test3D.h"
#include "Test2D.h"

using namespace ph;
using namespace renderer;

class Game : public Application {
public:
	Game() : Application("Phoebe", { 1600, 900, false, true }) { }

	void Game::Init() override {
		Application::Init();
		PushScene(new Test3D());
		// PushLayer(new Test2D());
	}
};

int main(int argc, char* args[]) {
	Game game;
	game.Start();
	return 0;
}