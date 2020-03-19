#ifndef WAVE_SYNTH_H
#define WAVE_SYNTH_H

#include <math.h>

#include "sample_source.h"

template <typename gens>
class WaveSynth : public SampleSource {
   public:
	WaveSynth(double freq) : m_freq(freq) {
	}

	~WaveSynth() {
	}

	void init(uint32_t sampleFreq, int amplitude) {
		m_sampleFreq = sampleFreq;
		m_pos = 0;
		m_inc = 1.0 / (double(m_sampleFreq) / m_freq);
		m_amplitude = double(amplitude) / 100.0;
		m_done = false;
	}

	double next() {
		double s = gens::genf(m_pos) * m_amplitude;
		m_pos += m_inc;
		if (m_pos > 1.0) {
			m_pos -= 1.0;
		}
		return s;
	}

	void release() {
		m_done = true;
	}
	bool done() {
		return m_done;
	}

   private:
	uint32_t m_sampleFreq;
	double m_freq;
	double m_pos;
	double m_inc;
	double m_amplitude;
	bool m_done;
};

struct sine_genf {
	static inline double genf(double pos) {
		return sin(pos * (M_PI * 2));
	}
};

struct square_genf {
	static inline double genf(double pos) {
		return ((pos < 0.5) ? 0.9 : -0.9);
	}
};

struct saw_genf {
	static inline double genf(double pos) {
		return (pos * 2.0 - 1.0);
	}
};

struct tri_genf {
	static inline double genf(double pos) {
		return ((pos < 0.5 ? pos : 1.0 - pos) * 4 - 1.0);
	}
};

typedef WaveSynth<sine_genf> SineWaveSynth;
typedef WaveSynth<square_genf> SquareWaveSynth;
typedef WaveSynth<saw_genf> SawWaveSynth;
typedef WaveSynth<tri_genf> TriangleWaveSynth;

class NoiseWaveSynth : public SampleSource {
   public:
	NoiseWaveSynth(double freq);
	~NoiseWaveSynth();

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
