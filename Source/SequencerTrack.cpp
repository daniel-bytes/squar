#include "SequencerTrack.h"

SequencerTrack::SequencerTrack(int numSteps)
{
	for (int i = 0; i < numSteps; i++) {
		steps.add(new SequencerElement(0,0));
	}
}

SequencerTrack::~SequencerTrack()
{
	for (auto step : steps) {
		delete step;
	}

	steps.clear();
}

void SequencerTrack::setStep(int step, SequencerElement &element)
{
	steps[step]->copy(element);
}

SequencerElement* SequencerTrack::getStep(int step) const
{
	return steps[step];
}
