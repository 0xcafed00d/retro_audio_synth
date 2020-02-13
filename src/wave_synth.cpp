
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
	m_done = false;
}

double SineWaveSyth::next() {
	double s = sin(m_pos) * m_amplitude;
	m_pos += m_inc;
	return s;
}

void SineWaveSyth::release() {
	m_done = true;
}

bool SineWaveSyth::done() {
	return m_done;
}

// ------------------------------------------------------------------

SquareWaveSyth::SquareWaveSyth(double freq) : m_freq(freq) {
}

SquareWaveSyth::~SquareWaveSyth() {
}

void SquareWaveSyth::init(uint32_t sampleFreq, int amplitude) {
	m_sampleFreq = sampleFreq;
	m_pos = 0;
	m_inc = 1.0 / (double(m_sampleFreq) / m_freq);
	m_amplitude = double(amplitude) / 100.0;
	m_done = false;
}

double SquareWaveSyth::next() {
	double s = ((m_pos < 0.5) ? 0.9 : -0.9) * m_amplitude;
	m_pos += m_inc;
	if (m_pos >= 1) {
		m_pos -= 1;
	}
	return s;
}

void SquareWaveSyth::release() {
	m_done = true;
}

bool SquareWaveSyth::done() {
	return m_done;
}
