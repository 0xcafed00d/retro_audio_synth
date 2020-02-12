#include <SDL2/SDL.h>

#include <iostream>

#include "adsr_synth.h"
#include "audio.h"
#include "wavtools.h"

int main(void) {
	try {
		AUDIO_Init();

		ADSRSynth gen(Waveform::SINE, 440, 200, 500, 20, 200);

		saveWav("test.wav", &gen, 22050, 100, 1000);

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
