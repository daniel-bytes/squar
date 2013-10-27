#include "InterfaceComponent.h"


void InterfaceComponent::addParameter(Parameter *parameter) {
	parameters.add(parameter);
	parameter->setInterfaceListener(this);
}

void InterfaceComponent::notifyEngine(float value, int index) {
	parameters[index]->setAndNotifyEngine(value);
}


void InterfaceComponent::parameterChanged(const Parameter *value)
{
	// let overriding class handle value
}
