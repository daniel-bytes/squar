#ifndef __SHIFTRENGINE_H__
#define __SHIFTRENGINE_H__

#include "DspProcessorGroup.h"

class Oscillator;

class ShiftrEngine
	: public DspProcessor
{
public:
	ShiftrEngine();
	~ShiftrEngine();

public:
	virtual void processMidi(MidiBuffer& midiMessages);

	virtual Array<Parameter*> getParameters(void);

	virtual float process(float input, int channel);

	virtual void init(double sampleRate, int numInputChannels, int numOutputChannels);

	virtual Array<ParameterListener*> getChildListeners();

private:
	Array<Oscillator*> oscillators;
};


#endif //__SHIFTRENGINE_H__
