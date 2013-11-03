#ifndef __CLOCKHANDLER_H__
#define __CLOCKHANDLER_H__

#include "../JuceLibraryCode/JuceHeader.h"

class ClockHandler
{
public:
	ClockHandler()
	{
		setStepSize(16);
	}

	ClockHandler(int stepSize)
	{
		setStepSize(stepSize);
	}

public:
	int getStepSize() const { 
		return resolution / ppq; 
	}

	void setStepSize(int stepSize) {
		ppq = resolution / stepSize;
	}

	virtual void onTrigger(int step) = 0;

protected:
	virtual void handleClock(AudioPlayHead::CurrentPositionInfo &position);

private:
	static const int resolution = 96;
	int ppq;
};

#endif //__CLOCKHANDLER_H__