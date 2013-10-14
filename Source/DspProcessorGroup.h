#ifndef __DSPPROCESSORGROUP_H__
#define __DSPPROCESSORGROUP_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "DspProcessor.h"

class DspProcessorGroup
	: DspProcessor
{
public:
	DspProcessorGroup(double sampleRate, int numInputChannels, int numOutputChannels)
		: DspProcessor(sampleRate, numInputChannels, numOutputChannels)
	{
	}

	virtual ~DspProcessorGroup();

public:
	virtual float process(float input, int channel);

	virtual void parameterChanged(Parameter *value);

	void Push(DspProcessor *processor)
	{
		processors.add(processor);
	}

private:
	Array<DspProcessor*> processors;
};

#endif //__DSPPROCESSORGROUP_H__