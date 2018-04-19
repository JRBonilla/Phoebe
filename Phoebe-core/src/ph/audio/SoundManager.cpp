#include "SoundManager.h"

namespace ph{ namespace audio  {

	gau_Manager*        SoundManager::m_Manager = nullptr;
	ga_Mixer*           SoundManager::m_Mixer = nullptr;
	std::vector<Sound*> SoundManager::m_Sounds;

	void SoundManager::Init() {
		gc_initialize(nullptr);
		m_Manager = gau_manager_create();
		m_Mixer = gau_manager_mixer(m_Manager);
	}

	void SoundManager::Add(Sound* sound) {
		m_Sounds.push_back(sound);
	}

	void SoundManager::Remove(Sound* sound) {
		for (uint i = 0; i < m_Sounds.size(); i++) {
			if (m_Sounds[i]->GetName() == sound->GetName()) {
				m_Sounds.erase(m_Sounds.begin() + i);
				break;
			}
		}
	}

	Sound* SoundManager::Get(const std::string& name) {
		for (Sound* sound: m_Sounds) {
			if (sound->GetName() == name) {
				return sound;
			}
		}
		return nullptr;
	}

	void SoundManager::Update() {
		gau_manager_update(m_Manager);
	}

	void SoundManager::Clean() {
		for (uint i = 0; i < m_Sounds.size(); i++) {
			delete m_Sounds[i];
		}
		gau_manager_destroy(m_Manager);
		gc_shutdown();
	}

}}