#include "adsr_synth.h"

ADSRSynth::ADSRSynth(Waveform w, int a, int d, int s, int r) {
}

ADSRSynth::~ADSRSynth() {
}

void ADSRSynth::init(uint32_t sampleFreq) {
	m_sampleFreq = sampleFreq;
}

int16_t ADSRSynth::next() {
	return 0;
}

void ADSRSynth::release() {
}

bool ADSRSynth::done() {
	return true;
}
