#include "Parameters.h"

Parameters::Parameters()
{
}

Parameters::~Parameters()
{
	for (auto p : parameters)
	{
		delete p;
	}

	parameters.clear();
}

void Parameters::registerListener(ParameterListener *listener)
{
	auto params = listener->getParameters();

	parameters.addArray(params);

	for (int i = 0; i < params.size(); i++) {
		listenerLookups.add(listener);
	}

	// walk any children and recursively register
	auto children = listener->getChildListeners();

	for (int i = 0; i < children.size(); i++) {
		auto child = children[i];
		this->registerListener(child);
	}
}

void Parameters::set(int index, float value)
{
	auto parameter = get(index);
	parameter->value = value;
	
	auto listener = listenerLookups[index];
	listener->parameterChanged(parameter);
}

void Parameters::initListeners()
{
	for (int i = 0; i < listenerLookups.size(); i++) {
		auto parameter = parameters[i];

		listenerLookups[i]->parameterChanged(parameter);
	}
}