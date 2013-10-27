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

String Oscillator::getParameterDisplayName(OscillatorParameters parameterType)
{
	switch(parameterType)
	{
	case kOscillatorParameters_Gain:
		return "Gain";
	case kOscillatorParameters_Freq:
		return "Frequency";
	case kOscillatorParameters_Waveform:
		return "Waveform";
	case kOscillatorParameters_Attack:
		return "Attack";
	case kOscillatorParameters_Decay:
		return "Decay";
	default:
		return "";
	}
}

String Oscillator::getParameterName(OscillatorParameters parameterType)
{
	String name = getParameterDisplayName(parameterType);

	name << " " << id;

	return name;
}

void Oscillator::trigger(float velocity)
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
	
	return wave * gain * env * velocity;
}

PointerArray<Parameter> Oscillator::getParameters()
{
	PointerArray<Parameter> parameters;
	String name;

	name = getParameterName(kOscillatorParameters_Gain);
	name << " " << id;
	Parameter *gain = new Parameter(kOscillatorParameters_Gain, name, name, .25);
	gain->setEngineListener(this);
	parameters.add(gain);
	
	name = getParameterName(kOscillatorParameters_Freq);
	name << " " << id;
	Parameter *freq = new Parameter(kOscillatorParameters_Freq, name, name, .25);
	freq->setEngineListener(this);
	parameters.add(freq);
	
	name = getParameterName(kOscillatorParameters_Waveform);
	name << " " << id;
	Parameter *wave = new Parameter(kOscillatorParameters_Waveform, name, name, .5);
	wave->setEngineListener(this);
	parameters.add(wave);
	
	name = getParameterName(kOscillatorParameters_Attack);
	name << " " << id;
	Parameter *attack = new Parameter(kOscillatorParameters_Attack, name, name, 0.05);
	attack->setEngineListener(this);
	parameters.add(attack);
	
	name = getParameterName(kOscillatorParameters_Decay);
	name << " " << id;
	Parameter *decay = new Parameter(kOscillatorParameters_Decay, name, name, .5);
	decay->setEngineListener(this);
	parameters.add(decay);

	return parameters;
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