#ifndef __ADENVELOPE_H__
#define __ADENVELOPE_H__

#include "DspElement.h"

enum class ADEnvelopeState
{
	Off,
	Rising,
	Falling,
	NumTypes
};

class ADEnvelope
	: public DspElement
{
public:
	ADEnvelope()
		: level(0), attack(0), decay(1), state(ADEnvelopeState::Off)
	{
	}

public:
	void trigger() {
		state = ADEnvelopeState::Rising;
		level = 0.f;
	}

	void setAttack(float value) {
		this->attack = value;
	}

	void setDecay(float value) {
		this->decay = value;
	}

public:
	virtual float process(float input, int channel);

private:
	float level;
	float attack;
	float decay;
	ADEnvelopeState state;
};

#endif //__ADENVELOPE_H__
