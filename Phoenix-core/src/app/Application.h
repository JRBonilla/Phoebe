#pragma once

namespace ph {

	class Application {
	public:
		Application();
		~Application();

		void Start();
		void Stop();
		void Pause();
		void Resume();
	};

}