#include "Oscillator.h"

float Oscillator::process(float input, int channel)
{
	float value = Phasor::process(input, channel);

	return (value * gain * 2.0);
}

void Oscillator::parameterChanged(Parameter *value)
{
	switch(value->type)
	{
	case kParameterType_Freq:
		this->setFrequency((value->value * 5000) + 100);
		break;

	case kParameterType_Gain:
		this->setGain(value->value);
		break;
	}
}