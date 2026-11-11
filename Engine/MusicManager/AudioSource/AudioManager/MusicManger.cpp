#include "MusicManger.h"
#include <alc.h>

ALCcontext* MusicManger::context = nullptr;
ALCdevice* MusicManger::device = nullptr;

void MusicManger::Init()
{
	device = alcOpenDevice(nullptr);
	if (!device)
		return;

	context = alcCreateContext(device, nullptr);
	if (!context)
	{
		alcCloseDevice(device);
		return;
	}

	alcMakeContextCurrent(context);
}



void MusicManger::ShutDown()
{
	alcMakeContextCurrent(nullptr);

	if (context)
		alcDestroyContext(context);

	if (device)
		alcCloseDevice(device);
}

MusicManger::~MusicManger()
{
	alcMakeContextCurrent(nullptr);

	if (context)
		alcDestroyContext(context);

	if (device)
		alcCloseDevice(device);
}
