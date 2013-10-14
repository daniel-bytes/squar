#ifndef __PHASOR_H__
#define __PHASOR_H__

#include "DspProcessor.h"

class Phasor
	: public DspProcessor
{
public:
	Phasor(double sampleRate, int numInputChannels, int numOutputChannels, float frequency)
		: DspProcessor(sampleRate, numInputChannels, numOutputChannels)
	{
		this->frequency = frequency;
		this->increment = 0;
		this->value = 0;

		this->configureIncrement();
	}

	virtual ~Phasor()
	{
	}

public:
	virtual float process(float input, int channel);

public:
	float getFrequency() const { return frequency; }
	
	void setFrequency(float value) {
		frequency = value;
		configureIncrement();
	}

private:
	void configureIncrement();

private:
	float increment;
	float frequency;
	float value;
};

#endif // __PHASOR_H__