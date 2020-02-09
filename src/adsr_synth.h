#ifndef ADSR_SYNTH_H
#define ADSR_SYNTH_H

#include "audio.h"

enum class Waveform { SINE, SQUARE, SAW, TRI, NOISE };

class ADSRSynth : public Generator {
   public:
	ADSRSynth(Waveform w, int a, int d, int s, int r);
	~ADSRSynth();

	void init(uint32_t sampleFreq);

	int16_t next();
	void release();
	bool done();

   private:
	uint32_t m_sampleFreq;
};

#endif /* ADSR_SYNTH_H */
