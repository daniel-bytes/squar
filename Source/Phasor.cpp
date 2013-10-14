#include "Phasor.h"

void Phasor::configureIncrement()
{
	increment = (1.0 / sampleRate) * frequency;
}

float Phasor::process(float input, int channel)
{
	if ((value += increment) >= .5) {
		value -= 1.0;
	}

	return value;
}