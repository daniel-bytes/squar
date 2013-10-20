#ifndef __SHIFTRENGINE_H__
#define __SHIFTRENGINE_H__

#include "DspProcessorGroup.h"

#define NUM_TRACKS 1
#define NUM_STEPS_PER_TRACK 16

class Oscillator;
class Sequencer;

class ShiftrEngine
	: public DspProcessor
{
public:
	ShiftrEngine();
	~ShiftrEngine();

public:
	virtual void processMidi(MidiBuffer& midiMessages, AudioPlayHead::CurrentPositionInfo& posInfo);

	virtual Array<Parameter*> getParameters(void);

	virtual float process(float input, int channel);

	virtual void init(double sampleRate, int numInputChannels, int numOutputChannels);

	virtual Array<ParameterListener*> getChildListeners();

private:
	Array<Oscillator*> oscillators;
	ScopedPointer<Sequencer> sequencer;
};


#endif //__SHIFTRENGINE_H__
