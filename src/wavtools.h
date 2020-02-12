#ifndef WAVTOOLS_H
#define WAVTOOLS_H

#include "audio.h"

bool saveWav(const char* name, Generator* gen, int sampleFreq, int amplitude, int releasems);

#endif /* WAVTOOLS_H */
