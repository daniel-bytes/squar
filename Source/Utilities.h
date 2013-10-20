#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <cmath>

inline float clip(float value, float min, float max)
{
	if (value > max) {
		return max;
	}
	else if (value < min) {
		return min;
	}

	return value;
}

inline float scale(float value, float min, float max)
{
	return (value * (max - min)) + min;
}

#endif //__UTILITIES_H__