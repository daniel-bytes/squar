#ifndef __ADENVELOPE_H__
#define __ADENVELOPE_H__

#include "DspElement.h"

enum ADEnvelopeState
{
	kADEnvelopeState_Off,
	kADEnvelopeState_Rising,
	kADEnvelopeState_Falling,
	kADEnvelopeState_NumStates
};

class ADEnvelope
	: public DspElement
{
public:
	ADEnvelope()
		: level(0), attack(0), decay(1), state(kADEnvelopeState_Off)
	{
	}

public:
	void trigger() {
		state = kADEnvelopeState_Rising;
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
