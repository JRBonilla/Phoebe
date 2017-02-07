#include "Sound.h"
#include "SoundManager.h"

namespace ph{ namespace audio {

	bool Sound::m_IsPlaying = false;

	Sound::Sound(const std::string& name, const std::string& filename) 
		: m_Name(name), m_Filename(filename) {
		m_Sound = gau_load_sound_file(m_Filename.c_str(), FileManager::GetFileExtension(filename).c_str());
		PHOENIX_ASSERT(m_Sound, "Could not load sound file " << m_Filename.c_str() << "!");
	}

	Sound::~Sound() {
		ga_sound_release(m_Sound);
	}


	void Sound::Play() {
		if (m_IsPlaying) {
			return;
		}
		gc_int32 quit = 0;
		m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &SetFlagAndDestroyOnFinish, &quit, nullptr);
		ga_handle_play(m_Handle);
		m_IsPlaying = true;
	}

	void Sound::Pause()
	{
		if (!m_IsPlaying) {
			return;
		}
		ga_handle_stop(m_Handle);
		m_IsPlaying = false;
	}

	void Sound::Resume()
	{
		if (m_IsPlaying) {
			return;
		}
		ga_handle_play(m_Handle);
		m_IsPlaying = true;
	}

	void Sound::Loop()
	{
		if (m_IsPlaying) {
			return;
		}
		gau_SampleSourceLoop* loopSrc;
		m_Handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, 0, 0, &loopSrc);
		ga_handle_play(m_Handle);
		m_IsPlaying = true;
	}

	void Sound::Stop()
	{
		if (!m_IsPlaying) {
			return;
		}
		ga_handle_stop(m_Handle);
		ga_handle_destroy(m_Handle);
		m_IsPlaying = false;
	}

	void Sound::SetFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
	{
		gc_int32* flag = static_cast<gc_int32*>(in_context);
		*flag = 1;
		ga_handle_destroy(in_handle);
		m_IsPlaying = false;
	}
}}
