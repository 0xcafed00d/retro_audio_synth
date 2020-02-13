#ifndef ADSR_SYNTH_H
#define ADSR_SYNTH_H

#include "sample_source.h"

class ADSRSynth : public SampleSource {
   public:
	ADSRSynth(int a, int d, int s, int r);
	~ADSRSynth();

	void connect(ConnectionPoint c, SampleSource* s);
	void init(uint32_t sampleFreq, int amplitude);

	double next();
	void release();
	bool done();

   private:
	uint32_t m_sampleFreq;
	uint32_t m_sampleCount;
	double m_amplitude;

	int m_adsr[4];
	double m_adsrRates[4];
	uint32_t m_adsrCounts[4];
	uint32_t m_adsrStage;
	double m_adsrAmplitude;
	double m_sustainAmplitude;
	bool m_done;

	SampleSource* m_source;
};

#endif /* ADSR_SYNTH_H */
