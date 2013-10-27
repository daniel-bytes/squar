#ifndef __INTERFACEVALUEPARAMETERADAPTER_H__
#define __INTERFACEVALUEPARAMETERADAPTER_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "InterfaceValueListener.h"

class Parameters;

class InterfaceValueParameterAdapter
	: public InterfaceValueListener
{
public:
	virtual void addParameter(Parameters *parameters, const String &parameterName);
	virtual void valueChanged(float value, int index = 0);

private:
	Parameters *parameters;
	Array<int> indexes;
};


#endif //__INTERFACEVALUEPARAMETERADAPTER_H__