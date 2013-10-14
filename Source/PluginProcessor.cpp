/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "DspProcessorGroup.h"
#include "Parameters.h"
#include "Oscillator.h"

//==============================================================================
ShiftrAudioProcessor::ShiftrAudioProcessor()
{
	parameters.add(new Parameter(kParameterType_Gain, "Gain", "Gain", 1.0));
	parameters.add(new Parameter(kParameterType_Freq, "Frequency", "Frequency", 1000.0));
}

ShiftrAudioProcessor::~ShiftrAudioProcessor()
{
	for (auto p : parameters)
	{
		delete p;
	}

	parameters.clear();
}

//==============================================================================
const String ShiftrAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int ShiftrAudioProcessor::getNumParameters()
{
	return kParameterType_NumParameters;
}

float ShiftrAudioProcessor::getParameter (int index)
{
	return parameters[index]->value;
}

void ShiftrAudioProcessor::setParameter (int index, float newValue)
{
	parameters[index]->value = newValue;
	this->processors->parameterChanged(parameters[index]);
}

const String ShiftrAudioProcessor::getParameterName (int index)
{
	return parameters[index]->name;
}

const String ShiftrAudioProcessor::getParameterText (int index)
{
	return parameters[index]->text;
}

const String ShiftrAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String ShiftrAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool ShiftrAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool ShiftrAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool ShiftrAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ShiftrAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ShiftrAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double ShiftrAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ShiftrAudioProcessor::getNumPrograms()
{
    return 0;
}

int ShiftrAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ShiftrAudioProcessor::setCurrentProgram (int index)
{
}

const String ShiftrAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void ShiftrAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ShiftrAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	int inputs = this->getNumInputChannels();
	int outputs = this->getNumOutputChannels();

	processors = new DspProcessorGroup(sampleRate, inputs, outputs);

	processors->Push(new Oscillator(sampleRate, inputs, outputs, parameters[kParameterType_Freq]->value, parameters[kParameterType_Gain]->value));
}

void ShiftrAudioProcessor::releaseResources()
{
	processors = nullptr;
}

void ShiftrAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);

		for (int i = 0; i < buffer.getNumSamples(); i++) {
			float data = *(channelData + i);

			data = processors->process(data, channel);

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
bool ShiftrAudioProcessor::hasEditor() const
{
    return false; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ShiftrAudioProcessor::createEditor()
{
    return new ShiftrAudioProcessorEditor (this);
}

//==============================================================================
void ShiftrAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ShiftrAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ShiftrAudioProcessor();
}
