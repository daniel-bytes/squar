#ifndef __OSCILLATOR_H__
#define __OSCILLATOR_H__

#include "DspProcessor.h"

class Phasor;
class ADEnvelope;

enum class OscillatorParameter
{
	Gain,
	Freq,
	Waveform,
	Attack,
	Decay,
	NumTypes
};

class Oscillator
	: public DspProcessor
{
public:
	Oscillator(int id);
	virtual ~Oscillator(void);

public:
	int getID(void) const { return id; }

public:
	virtual void trigger(float velocity);

public:
	virtual float process(float input, int channel);

	virtual void init(double sampleRate, int numInputChannels, int numOutputChannels);

	virtual void parameterChanged(const Parameter *value);

private:
	float getIncrement(void) const {
		return (1.0 / sampleRate) * frequency;
	}

private:
	int id;
	float gain;
	float frequency;
	float waveform;
	float velocity;

	ScopedPointer<Phasor> phasor;
	ScopedPointer<ADEnvelope> envelope;
};


#endif //__OSCILLATOR_H__