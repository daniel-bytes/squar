#ifndef __SEQUENCERCHANNEL_H__
#define __SEQUENCERCHANNEL_H__

#include "PointerArray.h"
#include "InterfaceComponent.h"

class SliderBoxControl;

class SequencerChannelControl
	: public InterfaceComponent
{
public:
	SequencerChannelControl(int numSteps, int stepsPerRow);
	~SequencerChannelControl();

public:
	void setStep(int index);

	void resized();

	void paint(Graphics &g);

private:
	int currentStep;
	int numSteps;
	int stepsPerRow;
	OwnedPointerArray<SliderBoxControl> sliders;

	void layoutControls();
};

#endif //__SEQUENCERCHANNEL_H__