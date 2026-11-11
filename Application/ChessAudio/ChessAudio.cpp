#include "ChessAudio.h"

ChessAudio::ChessAudio()
{


	BackGroundMusic.loadSound("C:/Users/User/Chess/Assets/Sound/__PlaceHolder__BackGroundMusic.wav");
	PieceCaptured.loadSound("C:/Users/User/Chess/Assets/Sound/__PlaceHolder__PieceMoveSound.wav");

	BackGroundMusic.setListener();
	PieceCaptured.setListener();

	BackGroundMusic.setAudioPlayer(1);
	PieceCaptured.setAudioPlayer(false);

	BackGroundMusic.SetVolume(0.5f);
	PieceCaptured.SetVolume(1.0f);

	BackGroundMusic.Play();
}

void ChessAudio::PlayPieceMoved()
{
	PieceCaptured.Play();
}

