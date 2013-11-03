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
	void configureParameter(Parameter *parameter);

	void appendComponent(InterfaceComponent *component, String id, bool visible, int x, int y, int width, int height);

protected:
	PointerArray<Parameter> parameters;
	OwnedPointerArray<InterfaceComponent> controls;
};

inline String createName(String parameterName, int channelNumber)
{
	parameterName << " " << channelNumber;
	return parameterName;
}


#endif //__INTERFACECOMPONENTS_H__