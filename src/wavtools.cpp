
#include "wavtools.h"

#include <stdio.h>

struct WavfileHeader {
	char riffTag[4] = {'R', 'I', 'F', 'F'};
	int riffLen = 0;
	char waveTag[4] = {'W', 'A', 'V', 'E'};
	char fmtTag[4] = {'f', 'm', 't', ' '};
	int fmtLen = 16;
	short audioFormat = 1;
	short numChannels = 1;
	int sampleRate = 22050;
	int byteRate = 44100;
	short blockAlign = 2;
	short bitsPerSample = 16;
	char dataTag[4] = {'d', 'a', 't', 'a'};
	int dataLength = 0;
};

bool saveWav(const char* name, Generator* gen, int sampleFreq, int amplitude, int releasems) {
	FILE* f = fopen(name, "wb+");
	if (!f) {
		return false;
	}

	WavfileHeader header;
	header.sampleRate = sampleFreq;
	header.byteRate = sampleFreq * 2;

	if (fwrite(&header, sizeof(header), 1, f) == 0) {
		fclose(f);
		return false;
	}

	gen->init(sampleFreq, amplitude);

	int releaseAt = releasems * sampleFreq / 1000;

	int sampleCount = 0;
	while (!gen->done()) {
		if (sampleCount == releaseAt) {
			gen->release();
		}
		auto s = gen->next();
		if (fwrite(&s, sizeof(s), 1, f) == 0) {
			fclose(f);
			return false;
		}
		sampleCount++;
	}

	header.dataLength = sampleCount * 2;
	header.riffLen = sizeof(header) + sampleCount * 2 - 8;

	fseek(f, 0, SEEK_SET);
	if (fwrite(&header, sizeof(header), 1, f) == 0) {
		fclose(f);
		return false;
	}

	fclose(f);
	return true;
}