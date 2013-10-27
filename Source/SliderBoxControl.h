#ifndef __SLIDERBOXCONTROL_H__
#define __SLIDERBOXCONTROL_H__

#include "InterfaceComponent.h"

enum SliderBoxControlOrientatons
{
	kSliderBoxControlOrientatons_Vertical,
	kSliderBoxControlOrientatons_Horizontal,
	kSliderBoxControlOrientatons_NumOrientations
};

class InterfaceValueListener;

class SliderBoxControl
	: public InterfaceComponent
{
public:
	SliderBoxControl(SliderBoxControlOrientatons orientation);
	~SliderBoxControl();

public:
	virtual void paint (Graphics& g);

	virtual void mouseDown (const MouseEvent &event);

	virtual void mouseDrag (const MouseEvent &event);

	virtual void handleMouseDown(const MouseEvent &event);

	virtual void parameterChanged(const Parameter *parameter);

	void setColour(Colour colour) {
		this->innerColour = colour;
	}

private:
	float value;
	SliderBoxControlOrientatons orientation;
	Colour innerColour;
};

#endif // __SLIDERBOXCONTROL_H__