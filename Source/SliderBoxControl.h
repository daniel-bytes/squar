#ifndef __SLIDERBOXCONTROL_H__
#define __SLIDERBOXCONTROL_H__

#include "InterfaceComponent.h"

enum class SliderBoxControlOrientaton
{
	Vertical,
	Horizontal,
	NumTypes
};

class InterfaceValueListener;

class SliderBoxControl
	: public InterfaceComponent
{
public:
	SliderBoxControl(SliderBoxControlOrientaton orientation);
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
	SliderBoxControlOrientaton orientation;
	Colour innerColour;
};

#endif // __SLIDERBOXCONTROL_H__