#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "../JuceLibraryCode/JuceHeader.h"

enum ParameterType
{
	kParameterType_Gain,
	kParameterType_Freq,
	kParameterType_NumParameters
};

struct Parameter
{
	ParameterType type;
	String name;
	String text;
	float value;

	Parameter(ParameterType type, String name, String text, float value)
	{
		this->type = type;
		this->name = name;
		this->text = text;
		this->value = value;
	}
};

class ParameterListener
{
	virtual void parameterChanged(Parameter *value) = 0;
};


#endif //__PARAMETERS_H__