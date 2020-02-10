#include "adsr_synth.h"

#include <math.h>

ADSRSynth::ADSRSynth(Waveform w, double freq, int a, int d, int s, int r)
    : m_freq(freq), m_adsr{a, d, s, r} {
}

ADSRSynth::~ADSRSynth() {
}

void ADSRSynth::init(uint32_t sampleFreq) {
	m_sampleFreq = sampleFreq;
	m_pos = 0;
	m_inc = double(m_sampleFreq) / m_freq;
	m_inc = (M_PI * 2) / m_inc;
}

int16_t ADSRSynth::next() {
	auto s = sin(m_pos) * 0x7000;
	m_pos += m_inc;
	return int16_t(s);
}

void ADSRSynth::release() {
}

bool ADSRSynth::done() {
	return false;
}
