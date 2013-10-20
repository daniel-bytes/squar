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
	for (auto track : tracks) {
		delete track;
	}

	tracks.clear();
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

Array<Parameter*> Sequencer::getParameters()
{
	Array<Parameter*> parameters;

	return parameters;
}

Array<ParameterListener*> Sequencer::getChildListeners()
{
	return Array<ParameterListener*>();
}
