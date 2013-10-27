#include "Sequencer.h"


Sequencer::Sequencer(int numTracks, int numSteps)
	: numSteps(numSteps), currentStep(-1), clockResolution(6)
{
	for (int i = 0; i < numTracks; i++) {
		tracks.add(new SequencerTrack(numSteps));
	}
}

Sequencer::~Sequencer()
{
}


void Sequencer::parameterChanged(const Parameter *value)
{

}

bool Sequencer::trigger(int clockCount)
{
	if ((clockCount % clockResolution) == 0) {
		if (++currentStep >= numSteps) {
			currentStep = 0;
		}

		return true;
	}

	return false;
}

PointerArray<Parameter> Sequencer::getParameters()
{
	PointerArray<Parameter> parameters;

	return parameters;
}

PointerArray<ParameterListener> Sequencer::getChildListeners()
{
	return PointerArray<ParameterListener>();
}
