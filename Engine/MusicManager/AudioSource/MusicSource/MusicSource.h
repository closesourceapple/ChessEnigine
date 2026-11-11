#pragma once
#include <string>


class AudioSource
{
public:
	AudioSource();
	~AudioSource();

	void setListener();
	void loadSound(std::string X_filePath);
	void setAudioPlayer(bool IS_looping);
	void SetVolume(float volume);
	void cleanUP();
	void Play();
	void Pause();
	void Resume();
	void Stop();

	inline int GetAudioID() { return m_AudioID; }

private:
	unsigned int m_AudioID = 0;
	unsigned int m_AudioPlayerID = 0;
};