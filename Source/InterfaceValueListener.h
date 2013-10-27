#ifndef __INTERFACEVALUELISTENER_H__
#define __INTERFACEVALUELISTENER_H__

class InterfaceValueListener
{
public:
	virtual void valueChanged(float value, int index = 0) = 0;
};


#endif //__INTERFACEVALUELISTENER_H__