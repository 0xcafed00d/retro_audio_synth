#include "adsr_synth.h"

#include <math.h>

#include <algorithm>

ADSRSynth::ADSRSynth(double freq, int a, int d, int s, int r) : m_freq(freq), m_adsr{a, d, s, r} {
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
	m_adsrAmplitude = 0;
	m_sustainAmplitude = m_adsr[2] / 100.0;
	m_done = false;

	m_adsrCounts[0] = m_adsr[0] * m_sampleFreq / 1000;
	m_adsrCounts[1] = m_adsr[1] * m_sampleFreq / 1000;
	m_adsrCounts[2] = 0;
	m_adsrCounts[3] = m_adsr[3] * m_sampleFreq / 1000;

	m_adsrRates[0] = 1.0 / m_adsrCounts[0];
	m_adsrRates[1] = (1.0 - m_sustainAmplitude) / m_adsrCounts[1];
	m_adsrRates[2] = 0;
	m_adsrRates[3] = m_sustainAmplitude / m_adsrCounts[3];
}

double ADSRSynth::next() {
	double s = sin(m_pos) * clamp(m_amplitude * m_adsrAmplitude);
	m_pos += m_inc;

	if (m_adsrStage == 0) {
		m_adsrAmplitude += m_adsrRates[0];
		if (m_sampleCount == m_adsrCounts[0]) {
			m_adsrStage = 1;
			m_sampleCount = 0;
		}
	} else if (m_adsrStage == 1) {
		m_adsrAmplitude -= m_adsrRates[1];
		if (m_sampleCount == m_adsrCounts[1]) {
			m_adsrStage = 2;
			m_sampleCount = 0;
		}
	} else if (m_adsrStage == 3) {
		m_adsrAmplitude -= m_adsrRates[3];
		if (m_sampleCount == m_adsrCounts[3]) {
			m_done = true;
		}
	}
	m_sampleCount++;
	return s;
}

void ADSRSynth::release() {
	m_adsrStage = 3;
	m_sampleCount = 0;
}

bool ADSRSynth::done() {
	return m_done;
}
