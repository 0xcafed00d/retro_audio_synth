
#include "wave_synth.h"

#include <math.h>

SineWaveSyth::SineWaveSyth(double freq) : m_freq(freq) {
}

SineWaveSyth::~SineWaveSyth() {
}

void SineWaveSyth::init(uint32_t sampleFreq, int amplitude) {
	m_sampleFreq = sampleFreq;
	m_pos = 0;
	m_inc = (M_PI * 2) / (double(m_sampleFreq) / m_freq);
	m_amplitude = double(amplitude) / 100.0;
	m_sampleCount = 0;
	m_done = false;
}

double SineWaveSyth::next() {
	double s = sin(m_pos) * m_amplitude;
	m_pos += m_inc;
	m_sampleCount++;
	return s;
}

void SineWaveSyth::release() {
	m_done = true;
}

bool SineWaveSyth::done() {
	return m_done;
}
