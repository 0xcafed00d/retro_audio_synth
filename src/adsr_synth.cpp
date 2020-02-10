#include "adsr_synth.h"

#include <math.h>

ADSRSynth::ADSRSynth(Waveform w, double freq, int a, int d, int s, int r)
    : m_freq(freq), m_adsr{a, d, s, r} {
}

ADSRSynth::~ADSRSynth() {
}

void ADSRSynth::init(uint32_t sampleFreq, int amplitude) {
	m_sampleFreq = sampleFreq;
	m_pos = 0;
	m_inc = (M_PI * 2) / (double(m_sampleFreq) / m_freq);
	m_amplitude = double(amplitude) / 100.0;
	m_sampleCount = 0;
	m_adsrStage = 0;
	m_adsrRates[2] = double(m_adsr[2]) / 100.0;
}

int16_t ADSRSynth::next() {
	auto s = sin(m_pos) * 32000 * m_amplitude;
	m_pos += m_inc;

	m_sampleCount++;
	return int16_t(s);
}

void ADSRSynth::release() {
}

bool ADSRSynth::done() {
	return false;
}
