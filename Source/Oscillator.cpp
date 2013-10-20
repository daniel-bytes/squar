#include "Oscillator.h"
#include "Phasor.h"
#include "ADEnvelope.h"
#include "Utilities.h"

Oscillator::Oscillator(int id)
{
	this->id = id;
	this->waveform = .5;
	this->gain = 1.0;

	this->phasor = new Phasor();
	this->envelope = new ADEnvelope();
}

Oscillator::~Oscillator()
{
	this->phasor = nullptr;
	this->envelope = nullptr;
}

void Oscillator::trigger()
{
	this->envelope->trigger();
}

void Oscillator::init(double sampleRate, int numInputChannels, int numOutputChannels)
{
	DspProcessor::init(sampleRate, numInputChannels, numOutputChannels);
	this->phasor->init(sampleRate, numInputChannels, numOutputChannels);
	this->envelope->init(sampleRate, numInputChannels, numOutputChannels);
}

float Oscillator::process(float input, int channel)
{
	float value = this->phasor->process(input, channel);
	float wave = (value >= this->waveform ? 1.f : -1.f);
	float env = this->envelope->process(input, channel);
	
	return wave * gain * env;
}

Array<Parameter*> Oscillator::getParameters()
{
	Array<Parameter*> parameters;
	
	Parameter *gain = new Parameter(kOscillatorParameters_Gain, "Gain", "Gain", .25);
	gain->name << " " << id;
	gain->text << " " << id;
	parameters.add(gain);

	Parameter *freq = new Parameter(kOscillatorParameters_Freq, "Freq", "Freq", .25);
	freq->name << " " << id;
	freq->text << " " << id;
	parameters.add(freq);

	Parameter *wave = new Parameter(kOscillatorParameters_Waveform, "Waveform", "Waveform", .5);
	wave->name << " " << id;
	wave->text << " " << id;
	parameters.add(wave);

	Parameter *attack = new Parameter(kOscillatorParameters_Attack, "Attack", "Attack", 0.05);
	attack->name << " " << id;
	attack->text << " " << id;
	parameters.add(attack);

	Parameter *decay = new Parameter(kOscillatorParameters_Decay, "Decay", "Decay", .5);
	decay->name << " " << id;
	decay->text << " " << id;
	parameters.add(decay);

	return parameters;
}

void Oscillator::parameterChanged(const Parameter *value)
{
	switch((OscillatorParameters)value->id)
	{
	case kOscillatorParameters_Freq:
		this->frequency = scale(value->value, 50.f, 2000.f);
		this->phasor->setFrequency(this->frequency);
		break;

	case kOscillatorParameters_Gain:
		this->gain = value->value;
		break;

	case kOscillatorParameters_Waveform:
		this->waveform = scale(value->value, .05f, .95f);
		break;

	case kOscillatorParameters_Attack:
		this->envelope->setAttack(value->value);
		break;

	case kOscillatorParameters_Decay:
		this->envelope->setDecay(value->value);
		break;
	}
}