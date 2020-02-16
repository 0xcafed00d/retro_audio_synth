#include <SDL2/SDL.h>

#include <iostream>

#include "adsr_synth.h"
#include "audio.h"
#include "wave_synth.h"
#include "wavtools.h"

int main(void) {
	try {
		AUDIO_Init();

		SineWaveSyth source(440);
		ADSRSynth envelope(200, 500, 20, 200);
		envelope.connect(ConnectionPoint::SOURCE, &source);

		saveWav("test.wav", &envelope, 22050, 100, 1000);

		AUDIO_Play(0, &envelope, 100);
		SDL_Delay(700);
		AUDIO_Release(0);
		SDL_Delay(1000);

		AUDIO_Shutdown();

	} catch (audio_exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}
