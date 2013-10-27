#ifndef __XYCONTROL_H__
#define __XYCONTROL_H__

#include "InterfaceComponent.h"

enum XYControlAxis
{
	kXYControlAxis_X,
	kXYControlAxis_Y,
	kXYControlAxis_NumAxis
};

class InterfaceDualValueListener;

class XYControl
	: public InterfaceComponent
{
public:
	XYControl();
	~XYControl();

public:
	virtual void paint (Graphics& g);

	virtual void mouseDown (const MouseEvent &event);

	virtual void mouseDrag (const MouseEvent &event);

	virtual void handleMouseDown(const MouseEvent &event);

	virtual void parameterChanged(const Parameter *parameter);

private:
	float posX;
	float posY;
};

#endif // __XYCONTROL_H__