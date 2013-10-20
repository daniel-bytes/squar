#ifndef __FILTER_H__
#define __FILTER_H__

#include "DspElement.h"

class Filter
	: public DspElement
{
public:
	virtual float process(int input, int channel);

private:
	float cutoff;
	float resonance;
	float value;
};

#endif //__FILTER_H__
