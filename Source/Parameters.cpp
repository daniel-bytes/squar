#include "Parameters.h"
#include "Utilities.h"

void Parameter::setEngineListener(ParameterListener *listener)
{
	this->engineListener = listener;
	this->engineListener->parameterChanged(this);
}

void Parameter::setInterfaceListener(ParameterListener *listener)
{
	this->interfaceListener = listener;
	this->interfaceListener->parameterChanged(this);
}

void Parameter::setAndNotifyEngine(float value)
{
	this->value = clip(value, 0.f, 1.f);
	
	if (this->engineListener != nullptr) {
		this->engineListener->parameterChanged(this);
	}
}

void Parameter::setAndNotifyInterface(float value)
{
	this->value = clip(value, 0.f, 1.f);
	
	if (this->interfaceListener != nullptr) {
		this->interfaceListener->parameterChanged(this);
	}
}

void Parameter::setAndNotifyAll(float value)
{
	this->value = clip(value, 0.f, 1.f);
	
	if (this->engineListener != nullptr) {
		this->engineListener->parameterChanged(this);
	}
	
	if (this->interfaceListener != nullptr) {
		this->interfaceListener->parameterChanged(this);
	}
}

void Parameters::initEngineListeners()
{
	for (auto p : parameters)
	{
		p->setAndNotifyEngine(p->getValue());
	}
}

void Parameters::initInterfaceListeners()
{
	for (auto p : parameters)
	{
		p->setAndNotifyInterface(p->getValue());
	}
}

void Parameters::initListeners()
{
	for (auto p : parameters)
	{
		p->setAndNotifyEngine(p->getValue());
		p->setAndNotifyInterface(p->getValue());
	}
}
