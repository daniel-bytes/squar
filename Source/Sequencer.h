#ifndef __SEQUENCER_H__
#define __SEQUENCER_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include "SequencerTrack.h"
#include "Parameters.h"

class Sequencer
	: public ParameterListener
{
public:
	Sequencer(int numTracks, int numSteps);
	~Sequencer();

public:
	void setStep(int track, int step, SequencerElement &element) { tracks[track]->setStep(step, element); }
	SequencerElement* getStep(int track, int step) const { return tracks[track]->getStep(step); }
	SequencerElement* getCurrentStep(int track) const { return tracks[track]->getStep(currentStep); }

	SequencerTrack* getTrack(int track) const { return tracks[track]; }

	int getNumSteps() const { return numSteps; }
	int getNumTracks() const { return tracks.size(); }
	int getCurrentStepNumber() const { return currentStep; }

public:
	bool trigger(int clockCount);

public:
	virtual void parameterChanged(const Parameter *value);
	virtual Array<Parameter*> getParameters();
	virtual Array<ParameterListener*> getChildListeners();

private:
	int numSteps;
	int currentStep;
	int clockResolution;
	Array<SequencerTrack*> tracks;
};

#endif //__SEQUENCER_H__