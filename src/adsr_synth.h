#ifndef ADSR_SYNTH_H
#define ADSR_SYNTH_H

#include "audio.h"

enum class Waveform { SINE, SQUARE, SAW, TRI, NOISE };

class ADSRSynth : public Generator {
   public:
	ADSRSynth(Waveform w, double freq, int a, int d, int s, int r);
	~ADSRSynth();

	void init(uint32_t sampleFreq, int amplitude);

	int16_t next();
	void release();
	bool done();

   private:
	uint32_t m_sampleFreq;
	uint32_t m_sampleCount;
	double m_freq;
	double m_pos;
	double m_inc;
	double m_amplitude;

	int m_adsr[4];
	double m_adsrRates[4];
	uint32_t m_adsrCounts[4];
	uint32_t m_adsrStage;
};

#endif /* ADSR_SYNTH_H */
