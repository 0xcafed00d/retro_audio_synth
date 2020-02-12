#ifndef SDL_AUDIO_H
#define SDL_AUDIO_H

#include <stdint.h>

#include <stdexcept>

#include "sample_source.h"

struct audio_exception : public std::runtime_error {
	using std::runtime_error::runtime_error;
};

void AUDIO_Init();
void AUDIO_Shutdown();

void AUDIO_Play(int chan, SampleSource* gen, int amplitude);
void AUDIO_Release(int chan);
void AUDIO_Stop(int chan);
bool AUDIO_isPlaying(int chan);

#endif /* SDL_AUDIO_H */
