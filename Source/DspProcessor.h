#ifndef __DSPPROCESSOR_H__
#define __DSPPROCESSOR_H__

#include "Parameters.h"

class DspProcessor
	: public ParameterListener
{
public:
	DspProcessor(double sampleRate, int numInputChannels, int numOutputChannels)
	{
		this->sampleRate = sampleRate;
		this->numInputChannels = numInputChannels;
		this->numOutputChannels = numOutputChannels;
	}

	virtual ~DspProcessor()
	{
	}

public:
	virtual float process(float input, int channel) = 0;

	virtual void parameterChanged(Parameter *value) { }

protected:
	double sampleRate;
	int numInputChannels;
	int numOutputChannels;
};

#endif //__DSPPROCESSOR_H__