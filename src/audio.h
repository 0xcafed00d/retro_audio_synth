#ifndef SDL_AUDIO_H
#define SDL_AUDIO_H

#include <stdint.h>

#include <stdexcept>

struct audio_exception : public std::runtime_error {
	using std::runtime_error::runtime_error;
};

// interface to a waveform generator
struct Generator {
	virtual void init(uint32_t sample_freq, int amplitude) = 0;
	virtual int16_t next() = 0;
	virtual void release() = 0;
	virtual bool done() = 0;
	virtual ~Generator() {
	}
};

void AUDIO_Init();
void AUDIO_Shutdown();

void AUDIO_Play(int chan, Generator* gen, int amplitude);
void AUDIO_Release(int chan);
void AUDIO_Stop(int chan);
bool AUDIO_isPlaying(int chan);

#endif /* SDL_AUDIO_H */
