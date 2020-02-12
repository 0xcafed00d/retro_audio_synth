#ifndef SAMPLESOURCE_H
#define SAMPLESOURCE_H

#include <stdint.h>

enum class ConnectionPoint { SOURCE, TREMOLO, VIBRATO };

// interface to a waveform Sample Source
struct SampleSource {
	virtual void connect(ConnectionPoint c, SampleSource* s){};
	virtual void init(uint32_t sample_freq, int amplitude) = 0;
	virtual double next() = 0;
	virtual void release() = 0;
	virtual bool done() = 0;
	virtual ~SampleSource() {
	}
};

inline double clamp(double val) {
	if (val < 0.0)
		return 0;
	if (val > 1.0)
		return 1.0;
	return val;
}

#endif /* SAMPLESOURCE_H */
