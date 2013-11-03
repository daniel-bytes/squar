#ifndef __OSCILLATORCHANNEL_H__
#define __OSCILLATORCHANNEL_H__

#include "InterfaceComponent.h"
#include "NoteSequencer.h"

class SliderBoxControl;

class OscillatorChannel
	: public InterfaceComponent, 
	  public NoteSequencerListener
{
public:
	OscillatorChannel(int channel, int noteNumber);
	~OscillatorChannel();

public:
	int getChannel() const { return channel; }
	int getNoteNumber() const { return noteNumber; }

	void parameterChanged(const Parameter *value);

	void handleNoteSequencer(int pitch, int velocity);

private:
	int channel;
	int noteNumber;
	ScopedPointer<NoteSequencer> sequencer;
};

#endif //__OSCILLATORCHANNEL_H__