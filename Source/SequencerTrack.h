#ifndef __SEQUENCERTRACK_H__
#define __SEQUENCERTRACK_H__

#include "../JuceLibraryCode/JuceHeader.h"

struct SequencerElement
{
	float velocity;
	int pitch;

	SequencerElement() {}

	SequencerElement(float velocity, int pitch) {
		this->velocity = velocity;
		this->pitch = pitch;
	}

	void copy(SequencerElement elem) {
		this->velocity = elem.velocity;
		this->pitch = elem.pitch;
	}
};

class SequencerTrack
{
public:
	SequencerTrack(int numSteps);
	~SequencerTrack();

public:
	void setStep(int step, SequencerElement &element);
	SequencerElement* getStep(int step) const;

	int getNumSteps() const { return steps.size(); }

private:
	Array<SequencerElement*> steps;
};

#endif //__SEQUENCERTRACK_H__