#include "Phasor.h"
#include "Utilities.h"

float Phasor::process(float input, int channel)
{
	float inc = (1.0 / sampleRate) * frequency;

	if ((value += inc) >= 1.f) {
		value -= 1.f;
	}

	return value;
}