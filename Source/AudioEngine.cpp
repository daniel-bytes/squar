#include "AudioEngine.h"
#include "Oscillator.h"
#include "Sequencer.h"

#define MIDI_START_NOTE 48

AudioEngine::AudioEngine()
{
	sequencer = new Sequencer(NUM_TRACKS, NUM_STEPS_PER_TRACK);

	for (int i = 1; i <= NUM_TRACKS; i++) {
		oscillators.add(new Oscillator(i));
	}

	// TODO : Remove!!!
	sequencer->setStep(0, 0, SequencerElement(1.0, 60));
	sequencer->setStep(0, 1, SequencerElement(0.0, 60));
	sequencer->setStep(0, 2, SequencerElement(0.0, 60));
	sequencer->setStep(0, 3, SequencerElement(0.0, 60));
	sequencer->setStep(0, 4, SequencerElement(0.0, 60));
	sequencer->setStep(0, 5, SequencerElement(0.0, 60));
	sequencer->setStep(0, 6, SequencerElement(0.0, 60));
	sequencer->setStep(0, 7, SequencerElement(0.0, 60));
	sequencer->setStep(0, 8, SequencerElement(1.0, 60));
	sequencer->setStep(0, 9, SequencerElement(0.0, 60));
	sequencer->setStep(0, 10, SequencerElement(0.0, 60));
	sequencer->setStep(0, 11, SequencerElement(0.0, 60));
	sequencer->setStep(0, 12, SequencerElement(0.0, 60));
	sequencer->setStep(0, 13, SequencerElement(0.0, 60));
	sequencer->setStep(0, 14, SequencerElement(0.0, 60));
	sequencer->setStep(0, 15, SequencerElement(0.0, 60));

	
	sequencer->setStep(1, 0, SequencerElement(0.0, 60));
	sequencer->setStep(1, 1, SequencerElement(0.0, 60));
	sequencer->setStep(1, 2, SequencerElement(0.0, 60));
	sequencer->setStep(1, 3, SequencerElement(0.0, 60));
	sequencer->setStep(1, 4, SequencerElement(1.0, 60));
	sequencer->setStep(1, 5, SequencerElement(0.0, 60));
	sequencer->setStep(1, 6, SequencerElement(0.0, 60));
	sequencer->setStep(1, 7, SequencerElement(0.0, 60));
	sequencer->setStep(1, 8, SequencerElement(0.0, 60));
	sequencer->setStep(1, 9, SequencerElement(0.0, 60));
	sequencer->setStep(1, 10, SequencerElement(0.0, 60));
	sequencer->setStep(1, 11, SequencerElement(0.0, 60));
	sequencer->setStep(1, 12, SequencerElement(1.0, 60));
	sequencer->setStep(1, 13, SequencerElement(0.0, 60));
	sequencer->setStep(1, 14, SequencerElement(0.0, 60));
	sequencer->setStep(1, 15, SequencerElement(0.0, 60));
}

AudioEngine::~AudioEngine()
{
	for (auto osc : oscillators)
	{
		delete osc;
	}

	oscillators.clear();

	sequencer = nullptr;
}

Array<Parameter*> AudioEngine::getParameters(void)
{
	Array<Parameter*> parameters;
	return parameters;
}

void AudioEngine::processMidi(MidiBuffer& midiMessages, AudioPlayHead::CurrentPositionInfo& posInfo)
{
	MidiBuffer::Iterator it(midiMessages);
	MidiMessage msg(0x80,0,0,0) ;
	int pos;

	while (it.getNextEvent(msg, pos)) {
		// Handle MIDI note events
		if (msg.isNoteOn(false)) {
			int oscToTrigger = msg.getNoteNumber() - MIDI_START_NOTE;
			if (oscToTrigger >= 0 && oscToTrigger < oscillators.size()) {
				oscillators[oscToTrigger]->trigger(1.f);
			}
		}
	}

	if (posInfo.isPlaying) {
		int iPos = int(posInfo.ppqPosition * 24.0);
		if (sequencer->trigger(iPos)) {
			for (int t = 0; t < NUM_TRACKS; t++) {
				auto step = sequencer->getCurrentStep(t);
				if (step->velocity > 0) {
					oscillators[t]->trigger(step->velocity);
				}
			}
		}
	}
}

float AudioEngine::process(float input, int channel)
{
	float value = 0.f;

	for (auto osc : oscillators)
	{
		float sample = osc->process(input, channel);
		value += (sample * .75);
	}

	return value;
}

void AudioEngine::init(double sampleRate, int numInputChannels, int numOutputChannels)
{
	DspProcessor::init(sampleRate, numInputChannels, numOutputChannels);

	for (auto osc : oscillators)
	{
		osc->init(sampleRate, numInputChannels, numOutputChannels);
	}
}

Array<ParameterListener*> AudioEngine::getChildListeners()
{
	Array<ParameterListener*> arr;
	arr.addArray(oscillators);
	arr.add(sequencer);

	return arr;
}