#include "DspProcessorGroup.h"



float DspProcessorGroup::process(float input, int channel)
{
	for (auto processor : processors)
	{
		input = processor->process(input, channel);
	}

	return input;
}

void DspProcessorGroup::parameterChanged(const Parameter *value)
{
	for (auto processor : processors)
	{
		processor->parameterChanged(value);
	}
}

PointerArray<ParameterListener> DspProcessorGroup::getChildListeners()
{
	PointerArray<ParameterListener> listeners;

	for (auto processor : processors)
	{
		listeners.add(processor);
	}

	return listeners;
}

void DspProcessorGroup::init(double sampleRate, int numInputChannels, int numOutputChannels)
{
	DspProcessor::init(sampleRate, numInputChannels, numOutputChannels);

	for (auto processor : processors)
	{
		processor->init(sampleRate, numInputChannels, numOutputChannels);
	}
}