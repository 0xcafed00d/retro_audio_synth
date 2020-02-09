#include <SDL2/SDL.h>

#include <iostream>

#include "audio.h"

int main(void) {
	try {
		AUDIO_Init();
	} catch (audio_exception& err) {
		std::cerr << err.what() << std::endl;
	}
	return 0;
}
