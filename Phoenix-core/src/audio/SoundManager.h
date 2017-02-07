#pragma once
#include <vector>
#include "Sound.h"
#include "../Types.h"

namespace ph{ namespace audio {

	class SoundManager
	{
	private:
		friend class Sound;
		static gau_Manager* m_Manager;
		static ga_Mixer* m_Mixer;
		static std::vector<Sound*> m_Sounds;
	public:
		static void Init();
		static void Update();
		static void Clean();

		static void Add(Sound* sound);
		static Sound* Get(const std::string& name);
	private:
		SoundManager() { }
	};

}}
