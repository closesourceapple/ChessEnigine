#pragma once

#include"../../Engine/MusicManager/AudioSource/MusicSource/MusicSource.h"
#include"../../Engine/MusicManager/AudioSource/AudioManager/MusicManger.h"

class ChessAudio
{
public:
	ChessAudio();
	void PlayPieceMoved();

private:
	AudioSource BackGroundMusic;
	AudioSource PieceCaptured;
};