#include "InterfaceValueParameterAdapter.h"
#include "Parameters.h"

void InterfaceValueParameterAdapter::addParameter(Parameters *parameters, const String &parameterName)
{
	int index = parameters->getIndexByName(parameterName);

	this->parameters = parameters;
	this->indexes.add(index);

	jassert(index > -1 && "Parameter not found!");
}

void InterfaceValueParameterAdapter::valueChanged(float value, int index)
{
	int idx = this->indexes[index];
	this->parameters->set(idx, value);
}

