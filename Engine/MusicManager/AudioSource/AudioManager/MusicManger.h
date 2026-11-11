#pragma once

typedef struct ALCdevice_struct ALCdevice;
typedef struct ALCcontext_struct ALCcontext;


static class MusicManger {
public:

	static void Init();
	static void ShutDown();
	~MusicManger();

private:
	static ALCdevice* device;
	static ALCcontext* context;
};