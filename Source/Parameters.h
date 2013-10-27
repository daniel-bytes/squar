#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PointerArray.h"

class ParameterListener;
class Parameter;
class Parameters;

/*
 * ParameterListener is a callback interface for a DSP processor to listen to parameter change events and 
 * configure their own parameters.
 */
class ParameterListener
{
public:
	virtual void parameterChanged(const Parameter *value) = 0;
};

/*
 * Parameter represents an individual parameter and it's current state/value.
 * Provides mappings to an engine and interface (UI) ParameterListener for callbacks
 * when the parameter state changes.
 */
class Parameter
{
public:
	Parameter(int id, String name, String text, float value)
		: engineListener(nullptr), interfaceListener(nullptr), id(id), name(name), text(text), value(value)
	{
	}

	int getID() const { return id; }
	String getName() const { return name; }
	String getText() const { return text; }
	float getValue() const { return value; }

	void setEngineListener(ParameterListener *listener);
	void setInterfaceListener(ParameterListener *listener);
	void setAndNotifyEngine(float value);
	void setAndNotifyInterface(float value);
	void setAndNotifyAll(float value);

private:
	int id;
	String name;
	String text;
	float value;
	ParameterListener *engineListener;
	ParameterListener *interfaceListener;
};

/*
 * Parameters represents a collection of parameters.
 * Parameter pointers are owned by this collection (will be deleted when Parameters goes out of scope).
 */
class Parameters
{
public:
	Parameter* get(int index) const { return parameters[index]; }
	int size(void) const { return this->parameters.size(); }

	void initEngineListeners();
	void initInterfaceListeners();
	void initListeners();

	void appendParameter(Parameter *parameter) {
		parameters.add(parameter);
	}

private:
	OwnedPointerArray<Parameter> parameters;
};



#endif //__PARAMETERS_H__