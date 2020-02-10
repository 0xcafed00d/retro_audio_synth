#include <SDL2/SDL.h>

#include <iostream>

#include "adsr_synth.h"
#include "audio.h"

int main(void) {
	try {
		AUDIO_Init();

		ADSRSynth gen(Waveform::SINE, 261.625565, 1, 2, 3, 4);

		AUDIO_Play(0, &gen);

		SDL_Delay(40000);

		AUDIO_Shutdown();

	} catch (audio_exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}
