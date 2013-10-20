#include "ShiftrEngine.h"
#include "Oscillator.h"

ShiftrEngine::ShiftrEngine()
{
	oscillators.add(new Oscillator(1));
}

ShiftrEngine::~ShiftrEngine()
{
	for (auto osc : oscillators)
	{
		delete osc;
	}

	oscillators.clear();
}

Array<Parameter*> ShiftrEngine::getParameters(void)
{
	Array<Parameter*> parameters;
	return parameters;
}

void ShiftrEngine::processMidi(MidiBuffer& midiMessages)
{
	MidiBuffer::Iterator it(midiMessages);
	MidiMessage msg(0x80,0,0,0) ;
	int pos;

	while (it.getNextEvent(msg, pos)) {
		if (msg.isNoteOn()) {
			if (msg.getNoteNumber() == 48) {
				oscillators[0]->trigger();
			}
		}
	}
}

float ShiftrEngine::process(float input, int channel)
{
	float value = 0.f;

	for (auto osc : oscillators)
	{
		float sample = osc->process(input, channel);
		value += (sample * .75);
	}

	return value;
}

void ShiftrEngine::init(double sampleRate, int numInputChannels, int numOutputChannels)
{
	DspProcessor::init(sampleRate, numInputChannels, numOutputChannels);

	for (auto osc : oscillators)
	{
		osc->init(sampleRate, numInputChannels, numOutputChannels);
	}
}

Array<ParameterListener*> ShiftrEngine::getChildListeners()
{
	Array<ParameterListener*> arr;
	arr.addArray(oscillators);

	return arr;
}