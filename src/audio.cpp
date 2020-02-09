#include "audio.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <stdint.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

static const int NUM_CHANNELS = 4;

struct Channel {
	Generator* gen = nullptr;
	bool playing = false;
};

static SDL_AudioDeviceID audioDevice = 0;
static std::array<Channel, NUM_CHANNELS> channels;

static void throw_error(std::string msg) {
	msg += SDL_GetError();
	throw(audio_exception(msg));
}

inline int16_t clamp(int32_t s) {
	if (s < INT16_MIN)
		return INT16_MIN;
	if (s > INT16_MAX)
		return INT16_MAX;
	return (int16_t)s;
}

static void callback(void* userdata, uint8_t* stream, int len) {
	int16_t* stream16 = (int16_t*)stream;
	for (int n = 0; n < len / 2; n++) {
		// bad mixing...
		int32_t sum = 0;
		for (int n = 0; n < NUM_CHANNELS; n++) {
			if (channels[n].playing) {
				sum += channels[n].gen->next() / 2;
				if (channels[n].gen->done()) {
					channels[n].playing = false;
					channels[n].gen = nullptr;
				}
			}
		}
		*stream16++ = clamp(sum);
	}
}

void AUDIO_Init() {
	if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
		throw_error("SDL_Init Error: ");
	}

	SDL_AudioSpec spec, gotspec;
	SDL_zero(spec);
	spec.freq = 22050;
	spec.format = AUDIO_S16LSB;
	spec.channels = 1;
	spec.samples = 2048;
	spec.callback = callback;
	audioDevice = SDL_OpenAudioDevice(nullptr, 0, &spec, &gotspec, 0);
	if (audioDevice == 0) {
		throw_error("SDL_OpenAudioDevice error: ");
	}
	SDL_PauseAudioDevice(audioDevice, 0);
}

void AUDIO_Shutdown() {
	SDL_PauseAudioDevice(audioDevice, 1);
	SDL_CloseAudioDevice(audioDevice);
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void AUDIO_Play(int chan, Generator* gen) {
	Channel ci;
	ci.gen = gen;
	ci.playing = true;
	gen->init(22050);

	SDL_LockAudioDevice(audioDevice);
	channels[chan] = ci;
	SDL_UnlockAudioDevice(audioDevice);
}

void AUDIO_Release(int chan) {
	SDL_LockAudioDevice(audioDevice);
	channels[chan].gen->release();
	SDL_UnlockAudioDevice(audioDevice);
}

void AUDIO_Stop(int chan) {
	SDL_LockAudioDevice(audioDevice);
	channels[chan].playing = false;
	channels[chan].gen = nullptr;
	SDL_UnlockAudioDevice(audioDevice);
}

bool AUDIO_isPlaying(int chan) {
	SDL_LockAudioDevice(audioDevice);
	bool playing = channels[chan].playing;
	SDL_UnlockAudioDevice(audioDevice);
	return playing;
}
