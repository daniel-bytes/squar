#ifndef __OSCILLATOR_H__
#define __OSCILLATOR_H__

#include "Phasor.h"

class Oscillator
	: public Phasor
{
public:
	Oscillator(double sampleRate, int numInputChannels, int numOutputChannels, float frequency, float gain)
		: Phasor(sampleRate, numInputChannels, numOutputChannels, frequency)
	{
		this->gain = gain;
	}

	virtual ~Oscillator()
	{
	}

public:
	virtual float process(float input, int channel);

	virtual void parameterChanged(Parameter *value);

public:
	float getGain() const { return gain; }
	void setGain(float value) { this->gain = value; }

private:
	float gain;
};

#endif //__OSCILLATOR_H__