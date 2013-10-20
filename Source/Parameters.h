#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "../JuceLibraryCode/JuceHeader.h"

class ParameterListener;
class Parameter;
class Parameters;

/*
 * Parameter represents an individual parameter and it's current state/value
 */
struct Parameter
{
	int id;
	String name;
	String text;
	float value;

	Parameter(int id, String name, String text, float value)
	{
		this->id = id;
		this->name = name;
		this->text = text;
		this->value = value;
	}
};

/*
 * Parameters represents a collection of parameters, mapped to ParameterListeners
 */
class Parameters
{
public:
	Parameters();
	~Parameters();

public:
	Parameter* get(int index) const { return parameters[index]; }
	int size(void) const { return this->parameters.size(); }

public:
	void registerListener(ParameterListener *listener);
	void set(int index, float value);
	void initListeners();

private:
	Array<Parameter*> parameters;
	Array<ParameterListener*> listenerLookups;
};

/*
 * ParameterListener is a callback interface for a DSP processor to listen to parameter change events and 
 * configure their own parameters.
 */
class ParameterListener
{
public:
	virtual void parameterChanged(const Parameter *value) = 0;
	virtual Array<Parameter*> getParameters() = 0;
	virtual Array<ParameterListener*> getChildListeners() = 0;
};



#endif //__PARAMETERS_H__