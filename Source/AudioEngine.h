#ifndef __AudioEngine_H__
#define __AudioEngine_H__

#include "DspProcessorGroup.h"

#define NUM_TRACKS 2
#define NUM_STEPS_PER_TRACK 16

class Oscillator;
class Sequencer;

class AudioEngine
	: public DspProcessor
{
public:
	AudioEngine();
	~AudioEngine();

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


#endif //__AudioEngine_H__
