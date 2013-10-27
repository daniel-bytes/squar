#include "XYControl.h"

Line<float> createXLine(Rectangle<int> bounds, float yPos)
{
	float y = (float)bounds.getHeight() * yPos;
	return Line<float>(0, y, bounds.getWidth(), y);
}

Line<float> createYLine(Rectangle<int> bounds, float xPos)
{
	float x = (float)bounds.getWidth() * xPos;
	return Line<float>(x, 0, x, bounds.getHeight());
}

XYControl::XYControl(void)
	: posX(.5), posY(.5)
{
	setSize(100, 100);
}

XYControl::~XYControl(void)
{
}


void XYControl::paint (Graphics& g)
{
	auto bounds = getLocalBounds();
	auto x = createXLine(bounds, posY);
	auto y = createYLine(bounds, posX);
	
	g.setColour(Colours::black);
	g.drawRect(bounds);

	g.drawLine(x, 1.f);
	g.drawLine(y, 1.f);
}

void XYControl::mouseDown (const MouseEvent &event)
{
	handleMouseDown(event);
}

void XYControl::mouseDrag (const MouseEvent &event)
{
	handleMouseDown(event);
}

void XYControl::handleMouseDown(const MouseEvent &event)
{
	auto bounds = getLocalBounds();
	auto position = event.getPosition();

	posX = (float)position.x / (float)bounds.getWidth();
	posY = (float)position.y / (float)bounds.getHeight();

	notifyEngine(posX, kXYControlAxis_X);
	notifyEngine(posY, kXYControlAxis_Y);

	repaint();
}

void XYControl::parameterChanged(const Parameter *parameter)
{
	if (parameters[0] == parameter) {
		posX = parameter->getValue();
	}
	else if (parameters[1] == parameter) {
		posY = parameter->getValue();
	}
}

