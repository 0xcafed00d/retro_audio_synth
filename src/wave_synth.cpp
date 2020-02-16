
#include "wave_synth.h"

// ------------------------------------------------------------------

NoiseWaveSynth::NoiseWaveSynth(double freq) {
}

NoiseWaveSynth::~NoiseWaveSynth() {
}

void NoiseWaveSynth::init(uint32_t sampleFreq, int amplitude) {
	m_amplitude = double(amplitude) / 100.0;
	m_done = false;
	m_rngstate = 12345;
}

double NoiseWaveSynth::next() {
	// https://en.wikipedia.org/wiki/Xorshift
	uint32_t x = m_rngstate;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	m_rngstate = x;

	return double(x) / (UINT32_MAX / 2) - 1.0;
}

void NoiseWaveSynth::release() {
	m_done = true;
}

bool NoiseWaveSynth::done() {
	return m_done;
}
