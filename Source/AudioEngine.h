#ifndef __AudioEngine_H__
#define __AudioEngine_H__

#include "PointerArray.h"
#include "DspProcessorGroup.h"

class Oscillator;
class Sequencer;
class Parameter;
class ParameterListener;
enum class OscillatorParameter;

class AudioEngine
	: public DspProcessor
{
public:
	AudioEngine();
	~AudioEngine();

public:
	virtual void processMidi(MidiBuffer& midiMessages, AudioPlayHead::CurrentPositionInfo& posInfo);

	virtual void configureParameters(Parameters *parameters);

	virtual float process(float input, int channel);

	virtual void init(double sampleRate, int numInputChannels, int numOutputChannels);

public:
	int getNumTracks() const { return 1; }

	int getNumStepsPerTrack() const { return 16; }

private:
	OwnedPointerArray<Oscillator> oscillators;
	ScopedPointer<Sequencer> sequencer;

	void appendParameter(Parameters *parameters, ParameterListener *engineListener, OscillatorParameter id, String name, String text, float value);
};


#endif //__AudioEngine_H__
