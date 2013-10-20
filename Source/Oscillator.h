#ifndef __OSCILLATOR_H__
#define __OSCILLATOR_H__

#include "DspProcessor.h"

class Phasor;
class ADEnvelope;

enum OscillatorParameters
{
	kOscillatorParameters_Gain,
	kOscillatorParameters_Freq,
	kOscillatorParameters_Waveform,
	kOscillatorParameters_Attack,
	kOscillatorParameters_Decay,
	kOscillatorParameters_NumParameters
};

class Oscillator
	: public DspProcessor
{
public:
	Oscillator(int id);
	virtual ~Oscillator(void);

public:
	virtual void trigger();

public:
	virtual float process(float input, int channel);

	virtual void init(double sampleRate, int numInputChannels, int numOutputChannels);

	virtual void parameterChanged(const Parameter *value);

	virtual Array<Parameter*> getParameters();

private:
	float getIncrement(void) const {
		return (1.0 / sampleRate) * frequency;
	}

private:
	int id;
	float gain;
	float frequency;
	float waveform;

	ScopedPointer<Phasor> phasor;
	ScopedPointer<ADEnvelope> envelope;
};

#endif //__OSCILLATOR_H__