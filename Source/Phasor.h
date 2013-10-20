#ifndef __PHASOR_H__
#define __PHASOR_H__

#include "DspElement.h"

class Phasor
	: public DspElement
{
public:
	Phasor()
		: value(0), frequency(1000)
	{
	}

public:
	virtual float process(float input, int channel);

public:
	void setFrequency(float value) {
		frequency = value;
	}

private:
	float frequency;
	float value;
};

#endif // __PHASOR_H__