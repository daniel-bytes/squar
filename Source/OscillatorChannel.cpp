#include "OscillatorChannel.h"
#include "SliderBoxControl.h"

OscillatorChannel::OscillatorChannel(int channel, int noteNumber)
	: channel(channel), noteNumber(noteNumber)
{
	appendComponent(new SliderBoxControl(SliderBoxControlOrientaton::Vertical), createName("Gain", channel), true, 5, 5, 25, 100);
	appendComponent(new SliderBoxControl(SliderBoxControlOrientaton::Vertical), createName("Frequency", channel), true, 35, 5, 25, 100);
	appendComponent(new SliderBoxControl(SliderBoxControlOrientaton::Vertical), createName("Waveform", channel), true, 65, 5, 25, 100);
	appendComponent(new SliderBoxControl(SliderBoxControlOrientaton::Vertical), createName("Attack", channel), true, 95, 5, 25, 100);
	appendComponent(new SliderBoxControl(SliderBoxControlOrientaton::Vertical), createName("Decay", channel), true, 125, 5, 25, 100);
	appendComponent(new NoteSequencer(16, 16, 16), createName("Sequencer", channel), true, 5, 110, 480, 480);
}

OscillatorChannel::~OscillatorChannel()
{
	sequencer = nullptr;
}

void OscillatorChannel::parameterChanged(const Parameter *value)
{
	// let children handle this one
}

void OscillatorChannel::handleNoteSequencer(int pitch, int velocity)
{
}