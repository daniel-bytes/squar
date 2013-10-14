#include "DspProcessorGroup.h"

DspProcessorGroup::~DspProcessorGroup()
{
	for (auto processor : processors)
	{
		delete processor;
	}
}

float DspProcessorGroup::process(float input, int channel)
{
	for (auto processor : processors)
	{
		input = processor->process(input, channel);
	}

	return input;
}

void DspProcessorGroup::parameterChanged(Parameter *value)
{
	for (auto processor : processors)
	{
		processor->parameterChanged(value);
	}
}