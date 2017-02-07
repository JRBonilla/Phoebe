#pragma once

#define GAU_THREAD_POLICY_MULTI 2

#include <iostream>
#include <gorilla/ga.h>
#include <gorilla/gau.h>
#include "../utils/FileManager.h"

namespace ph{ namespace audio {

	class Sound {
	private:
		static bool m_IsPlaying;
		std::string m_Name;
		std::string m_Filename;
		ga_Sound* m_Sound;
		ga_Handle* m_Handle;
	public:
		Sound(const std::string& name, const std::string& filename);
		~Sound();

		void Play();
		void Loop();
		void Pause();
		void Resume();
		void Stop();

		static void SetFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);

		inline const std::string& GetName() const { return m_Name; }
		inline const std::string& GetFilename() const { return m_Filename; }
	};

}}
