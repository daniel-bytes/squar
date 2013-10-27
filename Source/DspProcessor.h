#ifndef __DSPPROCESSOR_H__
#define __DSPPROCESSOR_H__

#include "DspElement.h"
#include "Parameters.h"

class DspProcessor
	: public DspElement, 
	  public ParameterListener
{
public:
	virtual float process(float input, int channel) = 0;

	virtual void parameterChanged(const Parameter *value) { }

	virtual PointerArray<Parameter> getParameters(void) { return PointerArray<Parameter>(); }
	
	virtual PointerArray<ParameterListener> getChildListeners() { return PointerArray<ParameterListener>(); }
};

#endif //__DSPPROCESSOR_H__