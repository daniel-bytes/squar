#include "SliderBoxControl.h"
#include "Utilities.h"

SliderBoxControl::SliderBoxControl(SliderBoxControlOrientatons orientation)
	: orientation(orientation), value(.5), innerColour(Colours::darkgrey)
{
	if (orientation == kSliderBoxControlOrientatons_Vertical) {
		setSize(25, 100);
	}
	else {
		setSize(100, 25);
	}
}

SliderBoxControl::~SliderBoxControl(void)
{
}


void SliderBoxControl::paint (Graphics& g)
{
	auto bounds = getLocalBounds();
	float width = bounds.getWidth();
	float height = bounds.getHeight();
	float borderWidth = 1.f;
	
	g.setColour(Colours::black);
	g.drawRect(bounds, borderWidth);
	
	g.setColour(innerColour);
	if (orientation == kSliderBoxControlOrientatons_Vertical) {
		float y = height - (height * value);
		g.fillRect(borderWidth, y + borderWidth, width - (borderWidth * 2.f), height - (borderWidth * 2.f));
	}
	else {
		float x = (width * value);
		g.fillRect(borderWidth, borderWidth, x - (borderWidth * 2.f), height - (borderWidth * 2.f));
	}
}

void SliderBoxControl::mouseDown (const MouseEvent &event)
{
	handleMouseDown(event);
}

void SliderBoxControl::mouseDrag (const MouseEvent &event)
{
	handleMouseDown(event);
}

void SliderBoxControl::handleMouseDown(const MouseEvent &event)
{
	auto bounds = getLocalBounds();
	auto position = event.getPosition();
	float height = bounds.getHeight();
	float width = bounds.getWidth();
	
	if (orientation == kSliderBoxControlOrientatons_Vertical) {
		value = 1.f - ((float)position.y / height);
	}
	else {
		value = (float)position.x / width;
	}
	
	value = clip(value, 0.f, 1.f);
	notifyEngine(value);

	repaint();
}

void SliderBoxControl::parameterChanged(const Parameter *parameter)
{
	value = parameter->getValue();
}