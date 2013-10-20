#ifndef __DSPELEMENT_H__
#define __DSPELEMENT_H__

class DspElement
{
public:
	virtual float process(float input, int channel) = 0;

	virtual void init(double sampleRate, int numInputChannels, int numOutputChannels)
	{
		this->sampleRate = sampleRate;
		this->numInputChannels = numInputChannels;
		this->numOutputChannels = numOutputChannels;
	}

protected:
	double sampleRate;
	int numInputChannels;
	int numOutputChannels;
};

#endif //__DSPELEMENT_H__