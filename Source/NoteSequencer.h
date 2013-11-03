#ifndef __NOTESEQUENCER_H__
#define __NOTESEQUENCER_H__

#include "InterfaceComponent.h"
#include "ClockHandler.h"

class NoteSequencerListener
{
public:
	virtual void handleNoteSequencer(int pitch, int velocity) = 0;
};

class NoteSequencerButton;

class NoteSequencer
	: public InterfaceComponent,
	  public ClockHandler
{
public:
	NoteSequencer(int numNotes, int numSteps, int clockResolution);
	~NoteSequencer();

public:
	int getNumNotes() const { return numNotes; }
	int getNumSteps() const { return numSteps; }

	virtual void addListener(NoteSequencerListener *listener) {
		listeners.add(listener);
	}

public:
	virtual void onTrigger(int step);
	void paint (Graphics& g);

	void resized();

	void parameterChanged(const Parameter *parameter) {}

	int getButtonIndex(int step, int note) {
		return note + (step * numNotes);
	}

	void buttonStateChanged(const NoteSequencerButton *button);

private:
	int numNotes;
	int numSteps;
	PointerArray<NoteSequencerListener> listeners;
	Array<int> pitches;
	Array<int> velocities;
	PointerArray<NoteSequencerButton> buttons;
};

#endif //__NOTESEQUENCER_H__