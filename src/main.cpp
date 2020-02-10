#include <SDL2/SDL.h>

#include <iostream>

#include "adsr_synth.h"
#include "audio.h"

int main(void) {
	try {
		AUDIO_Init();

		ADSRSynth gen(Waveform::SINE, 440 / 4, 1, 2, 3, 4);

		AUDIO_Play(0, &gen, 100);
		SDL_Delay(1000);
		AUDIO_Release(0);
		SDL_Delay(1000);

		AUDIO_Shutdown();

	} catch (audio_exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}
