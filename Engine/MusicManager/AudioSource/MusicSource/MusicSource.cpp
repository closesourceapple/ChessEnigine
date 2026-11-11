#include "MusicSource.h"
#include <al.h>
#include <alc.h>
#include <stdexcept>
#include "../../../Vendor/drWav/drWav.h"


AudioSource::AudioSource() {}
AudioSource::~AudioSource() {}


void AudioSource::setListener()
{
	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
}

void AudioSource::loadSound(std::string X_filePath)
{
	unsigned int channels;
	unsigned int sampleRate;
	drwav_uint64 totalFrames;

	drwav_int16* audioData =
		drwav_open_file_and_read_pcm_frames_s16(X_filePath.c_str(), &channels, &sampleRate, &totalFrames, NULL);

	if (audioData == nullptr)
		throw std::runtime_error("Failed to load WAV");
	ALenum format;

	if (channels == 1)
		format = AL_FORMAT_MONO16;
	else if (channels == 2)
		format = AL_FORMAT_STEREO16;
	else
	{
		drwav_free(audioData, NULL);
		throw std::runtime_error("Unsupported channel count");
	}

	alGenBuffers(1, &m_AudioID);
	ALsizei dataSize = static_cast<ALsizei>(
		totalFrames * channels * sizeof(drwav_int16)
		);

	alBufferData(m_AudioID, format, audioData, dataSize, sampleRate);

	drwav_free(audioData, NULL);
}

void AudioSource::cleanUP()
{
	alDeleteBuffers(1, &m_AudioID);
}

void AudioSource::setAudioPlayer(bool IS_looping)
{
	alGenSources(1, &m_AudioPlayerID);
	alSourcef(m_AudioPlayerID, AL_GAIN, 1);
	alSourcef(m_AudioPlayerID, AL_PITCH, 1);
	alSource3f(m_AudioPlayerID, AL_POSITION, 0, 0, 0);
	if (IS_looping == true)
	{
		alSourcei(m_AudioPlayerID, AL_LOOPING, AL_TRUE);
	}
}

void AudioSource::SetVolume(float volume)
{
	alSourcef(m_AudioPlayerID, AL_GAIN, volume);
}

void AudioSource::Play()
{
	alSourcei(m_AudioPlayerID, AL_BUFFER, m_AudioID);
	alSourcePlay(m_AudioPlayerID);
}
void AudioSource::Pause()
{
	alSourcePause(m_AudioPlayerID);
}
void AudioSource::Resume()
{
	alSourcePlay(m_AudioPlayerID);
}
void AudioSource::Stop()
{
	alSourceStop(m_AudioPlayerID);
}

