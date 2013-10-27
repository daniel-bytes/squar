#include "Oscillator.h"
#include "Phasor.h"
#include "ADEnvelope.h"
#include "Utilities.h"

Oscillator::Oscillator(int id)
{
	this->id = id;
	this->waveform = .5;
	this->gain = 1.0;
	this->velocity = 0;

	this->phasor = new Phasor();
	this->envelope = new ADEnvelope();
}

Oscillator::~Oscillator()
{
	this->phasor = nullptr;
	this->envelope = nullptr;
}

void Oscillator::trigger(float velocity)
{
	this->velocity = velocity;
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
	
	return wave * gain * env * velocity;
}

void Oscillator::parameterChanged(const Parameter *value)
{
	switch((OscillatorParameters)value->getID())
	{
	case kOscillatorParameters_Freq:
		this->frequency = scale(value->getValue(), 50.f, 2000.f);
		this->phasor->setFrequency(this->frequency);
		break;

	case kOscillatorParameters_Gain:
		this->gain = value->getValue();
		break;

	case kOscillatorParameters_Waveform:
		this->waveform = scale(value->getValue(), .05f, .95f);
		break;

	case kOscillatorParameters_Attack:
		this->envelope->setAttack(value->getValue());
		break;

	case kOscillatorParameters_Decay:
		this->envelope->setDecay(value->getValue());
		break;
	}
}