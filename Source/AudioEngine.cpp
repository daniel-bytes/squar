#include "AudioEngine.h"
#include "Oscillator.h"
#include "Sequencer.h"

#define MIDI_START_NOTE 48

AudioEngine::AudioEngine()
{
	sequencer = new Sequencer(getNumTracks(), getNumStepsPerTrack());

	oscillators.add(new Oscillator(1));
}

AudioEngine::~AudioEngine()
{
	sequencer = nullptr;
}

void AudioEngine::configureParameters(Parameters *parameters)
{
	// Oscillator 1
	appendParameter(parameters, oscillators[0], kOscillatorParameters_Gain, "Gain 1", "Gain 1", .25);
	appendParameter(parameters, oscillators[0], kOscillatorParameters_Freq, "Frequency 1", "Frequency 1", .25);
	appendParameter(parameters, oscillators[0], kOscillatorParameters_Waveform, "Waveform 1", "Waveform 1", .5);
	appendParameter(parameters, oscillators[0], kOscillatorParameters_Attack, "Attack 1", "Attack 1", .05);
	appendParameter(parameters, oscillators[0], kOscillatorParameters_Decay, "Decay 1", "Decay 1", .5);
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
			for (int t = 0; t < getNumTracks(); t++) {
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

void AudioEngine::appendParameter(Parameters *parameters, ParameterListener *engineListener, int id, String name, String text, float value)
{
	auto parameter = new Parameter(id, name, text, value);
	parameter->setEngineListener(engineListener);
	parameters->appendParameter(parameter);
}