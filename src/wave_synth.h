#ifndef WAVE_SYNTH_H
#define WAVE_SYNTH_H

#include "sample_source.h"

class SineWaveSyth : public SampleSource {
   public:
	SineWaveSyth(double freq);
	~SineWaveSyth();

	void init(uint32_t sampleFreq, int amplitude);

	double next();
	void release();
	bool done();

   private:
	uint32_t m_sampleFreq;
	double m_freq;
	double m_pos;
	double m_inc;
	double m_amplitude;
	bool m_done;
};

class SquareWaveSyth : public SampleSource {
   public:
	SquareWaveSyth(double freq);
	~SquareWaveSyth();

	void init(uint32_t sampleFreq, int amplitude);

	double next();
	void release();
	bool done();

   private:
	uint32_t m_sampleFreq;
	double m_freq;
	double m_pos;
	double m_inc;
	double m_amplitude;
	bool m_done;
};

class TriangleWaveSyth : public SampleSource {
   public:
	TriangleWaveSyth(double freq);
	~TriangleWaveSyth();

	void init(uint32_t sampleFreq, int amplitude);

	double next();
	void release();
	bool done();

   private:
	uint32_t m_sampleFreq;
	double m_freq;
	double m_pos;
	double m_inc;
	double m_amplitude;
	bool m_done;
};

class SawtoothWaveSyth : public SampleSource {
   public:
	SawtoothWaveSyth(double freq);
	~SawtoothWaveSyth();

	void init(uint32_t sampleFreq, int amplitude);

	double next();
	void release();
	bool done();

   private:
	uint32_t m_sampleFreq;
	double m_freq;
	double m_pos;
	double m_inc;
	double m_amplitude;
	bool m_done;
};

class NoiseWaveSyth : public SampleSource {
   public:
	NoiseWaveSyth(double freq);
	~NoiseWaveSyth();

	void init(uint32_t sampleFreq, int amplitude);

	double next();
	void release();
	bool done();

   private:
	uint32_t m_rngstate;
	double m_amplitude;
	bool m_done;
};

#endif /* WAVE_SYNTH_H */
