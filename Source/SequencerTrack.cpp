#include "SequencerTrack.h"

SequencerTrack::SequencerTrack(int numSteps)
{
	for (int i = 0; i < numSteps; i++) {
		steps.add(new SequencerElement(0,0));
	}
}

void SequencerTrack::setStep(int step, SequencerElement &element)
{
	steps[step]->copy(element);
}

SequencerElement* SequencerTrack::getStep(int step) const
{
	return steps[step];
}
