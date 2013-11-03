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

void InterfaceComponent::appendComponent(InterfaceComponent *component, String id, bool visible, int x, int y, int width, int height)
{
	component->setComponentID(id);

	if (visible) {
		addAndMakeVisible(component);
	}
	else {
		addChildComponent(component);
	}

	component->setBounds(x, y, width, height);
	controls.add(component);
}

void InterfaceComponent::configureParameter(Parameter *parameter)
{
	if (this->getComponentID() == parameter->getName()) {
		this->addParameter(parameter);
		parameter->setInterfaceListener(this);
	}

	for (InterfaceComponent *interfaceComponent : controls) {
		interfaceComponent->configureParameter(parameter);
	}
}