#include <cmath>

double midiNoteToFreq(int midi_note) {
	int a = 440;  // frequency of A (440Hz)
	return (a / 32) * pow(2, ((midi_note - 9) / 12));
}