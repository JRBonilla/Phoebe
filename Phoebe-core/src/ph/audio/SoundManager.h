#pragma once
#include <vector>
#include "ph/Types.h"
#include "ph/audio/Sound.h"

namespace ph{ namespace audio {

	class SoundManager {
	private:
		friend class Sound;
		static std::vector<Sound*> m_Sounds;
		static gau_Manager*        m_Manager;
		static ga_Mixer*           m_Mixer;
	public:
		static void Init();
		static void Update();
		static void Clean();

		static void Add(Sound* sound);
		static void Remove(Sound* sound);
		static Sound* Get(const std::string& name);
	private:
		SoundManager() {}
	};

}}
