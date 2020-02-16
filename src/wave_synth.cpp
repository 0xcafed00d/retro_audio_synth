
#include "wave_synth.h"

#include <math.h>

// ------------------------------------------------------------------

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

// ------------------------------------------------------------------

TriangleWaveSyth::TriangleWaveSyth(double freq) : m_freq(freq) {
}

TriangleWaveSyth::~TriangleWaveSyth() {
}

void TriangleWaveSyth::init(uint32_t sampleFreq, int amplitude) {
	m_sampleFreq = sampleFreq;
	m_pos = 0;
	m_inc = 1.0 / (double(m_sampleFreq) / m_freq);
	m_amplitude = double(amplitude) / 100.0;
	m_done = false;
}

double TriangleWaveSyth::next() {
	double s = ((m_pos < 0.5 ? m_pos : 1.0 - m_pos) * 4 - 1.0) * m_amplitude;
	m_pos += m_inc;
	if (m_pos >= 1) {
		m_pos -= 1;
	}
	return s;
}

void TriangleWaveSyth::release() {
	m_done = true;
}

bool TriangleWaveSyth::done() {
	return m_done;
}

// ------------------------------------------------------------------

SawtoothWaveSyth::SawtoothWaveSyth(double freq) : m_freq(freq) {
}

SawtoothWaveSyth::~SawtoothWaveSyth() {
}

void SawtoothWaveSyth::init(uint32_t sampleFreq, int amplitude) {
	m_sampleFreq = sampleFreq;
	m_pos = 0;
	m_inc = 1.0 / (double(m_sampleFreq) / m_freq);
	m_amplitude = double(amplitude) / 100.0;
	m_done = false;
}

double SawtoothWaveSyth::next() {
	double s = (m_pos * 2.0 - 1.0) * m_amplitude;
	m_pos += m_inc;
	if (m_pos >= 1) {
		m_pos -= 1;
	}
	return s;
}

void SawtoothWaveSyth::release() {
	m_done = true;
}

bool SawtoothWaveSyth::done() {
	return m_done;
}

// ------------------------------------------------------------------

NoiseWaveSyth::NoiseWaveSyth(double freq) {
}

NoiseWaveSyth::~NoiseWaveSyth() {
}

void NoiseWaveSyth::init(uint32_t sampleFreq, int amplitude) {
	m_amplitude = double(amplitude) / 100.0;
	m_done = false;
	m_rngstate = 12345;
}

double NoiseWaveSyth::next() {
	// https://en.wikipedia.org/wiki/Xorshift
	uint32_t x = m_rngstate;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	m_rngstate = x;

	return double(x) / (UINT32_MAX / 2) - 1.0;
}

void NoiseWaveSyth::release() {
	m_done = true;
}

bool NoiseWaveSyth::done() {
	return m_done;
}
