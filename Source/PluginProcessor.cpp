/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "AudioEngine.h"


//==============================================================================
SquarAudioProcessor::SquarAudioProcessor()
{
	parameters = new Parameters();
	engine = new AudioEngine();

	engine->configureParameters(parameters);
}

SquarAudioProcessor::~SquarAudioProcessor()
{
	engine = nullptr;
	parameters = nullptr;
}


int SquarAudioProcessor::getNumTracks() const
{
	return engine->getNumTracks();
}

int SquarAudioProcessor::getNumStepsPerTrack() const
{
	return engine->getNumStepsPerTrack();
}

//==============================================================================
const String SquarAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int SquarAudioProcessor::getNumParameters()
{
	return parameters->size();
}

float SquarAudioProcessor::getParameter (int index)
{
	auto parameter = parameters->get(index);
	return parameter->getValue();
}

void SquarAudioProcessor::setParameter (int index, float newValue)
{
	auto parameter = parameters->get(index);
	parameter->setAndNotifyAll(newValue);
}

const String SquarAudioProcessor::getParameterName (int index)
{
	auto parameter = parameters->get(index);
	return parameter->getName();
}

const String SquarAudioProcessor::getParameterText (int index)
{
	auto parameter = parameters->get(index);
	return parameter->getText();
}

Parameters* SquarAudioProcessor::getParameters() {
	return parameters;
}

const String SquarAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String SquarAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool SquarAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool SquarAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool SquarAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SquarAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SquarAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double SquarAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SquarAudioProcessor::getNumPrograms()
{
    return 0;
}

int SquarAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SquarAudioProcessor::setCurrentProgram (int index)
{
}

const String SquarAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void SquarAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SquarAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	int inputs = this->getNumInputChannels();
	int outputs = this->getNumOutputChannels();
	
	engine->init(sampleRate, inputs, outputs);
	parameters->initListeners();
}

void SquarAudioProcessor::releaseResources()
{
}

void SquarAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	AudioPlayHead::CurrentPositionInfo posInfo;
	this->getPlayHead()->getCurrentPosition(posInfo);
	engine->processMidi(midiMessages, posInfo);

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData(channel);

		for (int i = 0; i < buffer.getNumSamples(); i++) {
			float data = *(channelData + i);

			data = engine->process(data, channel);

			*(channelData + i) = data;
		}
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool SquarAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SquarAudioProcessor::createEditor()
{
    return new SquarAudioProcessorEditor (this);
}

//==============================================================================
void SquarAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SquarAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SquarAudioProcessor();
}
