#ifndef __INTERFACECOMPONENTS_H__
#define __INTERFACECOMPONENTS_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Parameters.h"

class InterfaceComponent
	: public Component,
	  public ParameterListener
{
public:
	virtual void addParameter(Parameter *parameter);
	virtual void notifyEngine(float value, int index = 0);

public:
	virtual void parameterChanged(const Parameter *value) = 0;

protected:
	PointerArray<Parameter> parameters;
};



#endif //__INTERFACECOMPONENTS_H__